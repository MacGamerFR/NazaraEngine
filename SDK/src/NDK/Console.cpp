// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Nazara Development Kit"
// For conditions of distribution and use, see copyright notice in Prerequisites.hpp

#include <NDK/Console.hpp>
#include <Nazara/Core/Unicode.hpp>
#include <Nazara/Lua/LuaState.hpp>
#include <Nazara/Platform/Event.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <NDK/World.hpp>

///TODO: For now is unable to display different color in the history, it needs a RichTextDrawer to do so

namespace Ndk
{
	namespace
	{
		const char s_inputPrefix[] = "> ";
		constexpr std::size_t s_inputPrefixSize = Nz::CountOf(s_inputPrefix) - 1;
	}

	/*!
	* \ingroup NDK
	* \class Ndk::Console
	* \brief NDK class that represents a console to help development with Lua scripting
	*/

	/*!
	* \brief Constructs a Console object with a world to interact with
	*
	* \param world World to interact with
	* \param size (Width, Height) of the console
	* \param instance Lua instance that will interact with the world
	*/

	Console::Console(World& world, const Nz::Vector2f& size, Nz::LuaState& state) :
	m_historyPosition(0),
	m_defaultFont(Nz::Font::GetDefault()),
	m_state(state),
	m_size(size),
	m_opened(false),
	m_characterSize(24)
	{
		Nz::MaterialRef backgroundMaterial = Nz::Material::New();
		backgroundMaterial->EnableBlending(true);
		backgroundMaterial->EnableDepthBuffer(false);
		backgroundMaterial->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
		backgroundMaterial->SetSrcBlend(Nz::BlendFunc_SrcAlpha);

		// History bakckground
		m_historyBackgroundSprite = Nz::Sprite::New();
		m_historyBackgroundSprite->SetColor(Nz::Color(80, 80, 160, 128));
		m_historyBackgroundSprite->SetMaterial(backgroundMaterial);

		m_historyBackground = world.CreateEntity();
		m_historyBackground->Enable(m_opened);
		m_historyBackground->AddComponent<Ndk::GraphicsComponent>().Attach(m_historyBackgroundSprite, -1);
		m_historyBackground->AddComponent<Ndk::NodeComponent>().SetParent(this);

		// History
		m_historyDrawer.SetCharacterSize(m_characterSize);
		m_historyDrawer.SetColor(Nz::Color(200, 200, 200));
		m_historyDrawer.SetFont(m_defaultFont);

		m_historyTextSprite = Nz::TextSprite::New();

		m_history = world.CreateEntity();
		m_history->Enable(m_opened);
		m_history->AddComponent<Ndk::GraphicsComponent>().Attach(m_historyTextSprite);

		Ndk::NodeComponent& historyNode = m_history->AddComponent<Ndk::NodeComponent>();
		historyNode.SetParent(this);

		// Input background
		m_inputBackgroundSprite = Nz::Sprite::New();
		m_inputBackgroundSprite->SetColor(Nz::Color(255, 255, 255, 200));
		m_inputBackgroundSprite->SetMaterial(backgroundMaterial);

		m_inputBackground = world.CreateEntity();
		m_inputBackground->Enable(m_opened);
		m_inputBackground->AddComponent<Ndk::GraphicsComponent>().Attach(m_inputBackgroundSprite, -1);
		m_inputBackground->AddComponent<Ndk::NodeComponent>().SetParent(this);

		// Input
		m_inputDrawer.SetColor(Nz::Color::Black);
		m_inputDrawer.SetCharacterSize(m_characterSize);
		m_inputDrawer.SetFont(m_defaultFont);
		m_inputDrawer.SetText(s_inputPrefix);

		m_inputTextSprite = Nz::TextSprite::New();
		m_inputTextSprite->Update(m_inputDrawer);

		m_input = world.CreateEntity();
		m_input->Enable(m_opened);
		m_input->AddComponent<Ndk::GraphicsComponent>().Attach(m_inputTextSprite);

		Ndk::NodeComponent& inputNode = m_input->AddComponent<Ndk::NodeComponent>();
		inputNode.SetParent(this);

		Layout();
	}

	/*!
	* \brief Adds a line to the console
	*
	* \param text New line of text
	* \param color Color for the text
	*/

	void Console::AddLine(const Nz::String& text, const Nz::Color& color)
	{
		AddLineInternal(text, color);
		RefreshHistory();
	}

	/*!
	* \brief Clears the console
	*/

	void Console::Clear()
	{
		m_historyLines.clear();
		RefreshHistory();
	}

	/*!
	* \brief Sends a character to the console
	*
	* \param character Character that will be added to the console
	*/

	void Console::SendCharacter(char32_t character)
	{
		switch (character)
		{
			case '\b':
			{
				Nz::String input = m_inputDrawer.GetText();
				if (input.GetLength() <= s_inputPrefixSize) // Prevent removal of the input prefix
					return; // Ignore if no user character is there

				input.Resize(-1, Nz::String::HandleUtf8);
				m_inputDrawer.SetText(input);
				break;
			}

			case '\r':
			case '\n':
				ExecuteInput();
				break;

			default:
			{
				if (Nz::Unicode::GetCategory(character) == Nz::Unicode::Category_Other_Control)
					return;

				m_inputDrawer.AppendText(Nz::String::Unicode(character));
				break;
			}
		}

		m_inputTextSprite->Update(m_inputDrawer);
	}

	/*!
	* \brief Sends an event to the console
	*
	* \param event Event to be takin into consideration by the console
	*/
	void Console::SendEvent(const Nz::WindowEvent& event)
	{
		switch (event.type)
		{
			case Nz::WindowEventType_TextEntered:
				SendCharacter(event.text.character);
				break;

			case Nz::WindowEventType_KeyPressed:
			{
				switch (event.key.code)
				{
					case Nz::Keyboard::Down:
					case Nz::Keyboard::Up:
					{
						if (event.key.code == Nz::Keyboard::Up)
							m_historyPosition = std::min<std::size_t>(m_commandHistory.size(), m_historyPosition + 1);
						else
						{
							if (m_historyPosition > 1)
								m_historyPosition--;
							else if (m_historyPosition == 0)
								m_historyPosition = 1;
						}

						if (!m_commandHistory.empty())
						{
							Nz::String text = m_commandHistory[m_commandHistory.size() - m_historyPosition];
							m_inputDrawer.SetText(s_inputPrefix + text);
							m_inputTextSprite->Update(m_inputDrawer);
						}
						break;
					}

					default:
						break;
				}
				break;
			}

			default:
				break;
		}
	}

	/*!
	* \brief Sets the character size
	*
	* \param size Size of the font
	*/

	void Console::SetCharacterSize(unsigned int size)
	{
		m_characterSize = size;

		m_historyDrawer.SetCharacterSize(m_characterSize);
		m_historyTextSprite->Update(m_historyDrawer);
		m_inputDrawer.SetCharacterSize(m_characterSize);
		m_inputTextSprite->Update(m_inputDrawer);

		Layout();
	}

	/*!
	* \brief Sets the console size
	*
	* \param size (Width, Height) of the console
	*/

	void Console::SetSize(const Nz::Vector2f& size)
	{
		m_size = size;
		m_historyBackgroundSprite->SetSize(m_size);
		Layout();
	}

	/*!
	* \brief Sets the text font
	*
	* \param font Reference to a valid font
	*
	* \remark Produces a NazaraAssert if font is invalid or null
	*/

	void Console::SetTextFont(Nz::FontRef font)
	{
		NazaraAssert(font && font->IsValid(), "Invalid font");

		m_defaultFont = std::move(font);
		m_historyDrawer.SetFont(m_defaultFont);
		m_inputDrawer.SetFont(m_defaultFont);

		Layout();
	}

	/*!
	* \brief Shows the console
	*
	* \param show Should the console be showed
	*/

	void Console::Show(bool show)
	{
		if (m_opened != show)
		{
			m_historyBackground->Enable(show);
			m_history->Enable(show);
			m_input->Enable(show);
			m_inputBackground->Enable(show);

			m_opened = show;
		}
	}

	/*!
	* \brief Adds a line to the history of the console
	*
	* \param text New line of text
	* \param color Color for the text
	*/

	void Console::AddLineInternal(const Nz::String& text, const Nz::Color& color)
	{
		m_historyLines.emplace_back(Line{color, text});
	}

	/*!
	* \brief Performs this action when an input is added to the console
	*/

	void Console::ExecuteInput()
	{
		Nz::String input = m_inputDrawer.GetText();
		Nz::String inputCmd = input.SubString(s_inputPrefixSize);
		m_inputDrawer.SetText(s_inputPrefix);

		if (m_commandHistory.empty() || m_commandHistory.back() != inputCmd)
			m_commandHistory.push_back(inputCmd);

		m_historyPosition = 0;

		AddLineInternal(input); //< With the input prefix

		if (!m_state.Execute(inputCmd))
			AddLineInternal(m_state.GetLastError(), Nz::Color::Red);

		RefreshHistory();
	}

	/*!
	* \brief Places the console according to its layout
	*/

	void Console::Layout()
	{
		unsigned int lineHeight = m_defaultFont->GetSizeInfo(m_characterSize).lineHeight;

		Ndk::NodeComponent& inputNode = m_input->GetComponent<Ndk::NodeComponent>();
		inputNode.SetPosition(0.f, m_size.y - lineHeight - 5.f);

		float historyHeight = m_size.y - lineHeight - 5.f - 2.f;
		m_historyBackgroundSprite->SetSize(m_size.x, historyHeight);

		m_maxHistoryLines = static_cast<unsigned int>(std::ceil(historyHeight / lineHeight));

		Ndk::NodeComponent& historyNode = m_history->GetComponent<Ndk::NodeComponent>();
		historyNode.SetPosition(0.f, historyHeight - m_maxHistoryLines * lineHeight);

		Ndk::NodeComponent& inputBackgroundNode = m_inputBackground->GetComponent<Ndk::NodeComponent>();
		inputBackgroundNode.SetPosition(0.f, historyHeight + 2.f);

		m_inputBackgroundSprite->SetSize(m_size.x, m_size.y - historyHeight);
	}

	/*!
	* \brief Refreshes the history of the console
	*/

	void Console::RefreshHistory()
	{
		m_historyDrawer.Clear();
		auto it = m_historyLines.end();
		if (m_historyLines.size() > m_maxHistoryLines)
			it -= m_maxHistoryLines;
		else
			it = m_historyLines.begin();

		for (unsigned int i = 0; i < m_maxHistoryLines; ++i)
		{
			if (m_maxHistoryLines - i <= m_historyLines.size() && it != m_historyLines.end())
			{
				m_historyDrawer.AppendText(it->text);
				++it;
			}

			m_historyDrawer.AppendText(Nz::String('\n'));
		}

		m_historyTextSprite->Update(m_historyDrawer);
	}
}
