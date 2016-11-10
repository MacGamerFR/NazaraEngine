// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Nazara Engine - Renderer module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Renderer/RenderWindow.hpp>
#include <Nazara/Core/Error.hpp>
#include <Nazara/Core/Thread.hpp>
#include <Nazara/Renderer/Renderer.hpp>
#include <Nazara/Renderer/Debug.hpp>

namespace Nz
{
<<<<<<< HEAD
	RenderWindow::RenderWindow(VideoMode mode, const String& title, WindowStyleFlags style, const ContextParameters& parameters) :
	RenderTarget(), Window()
	{
		ErrorFlags flags(ErrorFlag_ThrowException, true);
		Create(mode, title, style, parameters);
	}

	RenderWindow::RenderWindow(WindowHandle handle, const ContextParameters& parameters) :
	RenderTarget(), Window()
	{
		ErrorFlags flags(ErrorFlag_ThrowException, true);
		Create(handle, parameters);
	}

=======
>>>>>>> VulkanRenderer: Add RenderWindow wrapper
	RenderWindow::~RenderWindow()
	{
		// Nécessaire si Window::Destroy est appelé par son destructeur
		OnWindowDestroy();
	}

<<<<<<< HEAD
	bool RenderWindow::CopyToImage(AbstractImage* image, const Vector3ui& dstPos) const
	{
		#if NAZARA_RENDERER_SAFE
		if (!m_context)
		{
			NazaraError("Window has not been created");
			return false;
		}
		#endif

		return CopyToImage(image, Rectui(Vector2ui(0U), GetSize()), dstPos);
	}

	bool RenderWindow::CopyToImage(AbstractImage* image, const Rectui& rect, const Vector3ui& dstPos) const
	{
		#if NAZARA_RENDERER_SAFE
		if (!m_context)
		{
			NazaraError("Window has not been created");
			return false;
		}
		#endif

		Vector2ui windowSize = GetSize();

		#if NAZARA_RENDERER_SAFE
		if (!image)
		{
			NazaraError("Image must be valid");
			return false;
		}

		if (image->GetFormat() != PixelFormatType_RGBA8)
		{
			// Pour plus de facilité, évidemment on peut faire sauter cette règle avec un peu de gestion
			NazaraError("Image must be RGBA8-formatted");
			return false;
		}

		if (rect.x + rect.width > windowSize.x || rect.y + rect.height > windowSize.y)
		{
			NazaraError("Rectangle dimensions are out of window's bounds");
			return false;
		}

		Vector3ui imageSize = image->GetSize();
		if (dstPos.x + rect.width > imageSize.x || dstPos.y + rect.height > imageSize.y || dstPos.z > imageSize.z)
		{
			NazaraError("Cube dimensions are out of image's bounds");
			return false;
		}
		#endif

		const Context* currentContext = Context::GetCurrent();
		if (m_context != currentContext)
		{
			if (!m_context->SetActive(true))
			{
				NazaraError("Failed to activate context");
				return false;
			}
		}

		///TODO: Fast-path pour les images en cas de copie du buffer entier

		m_buffer.resize(rect.width*rect.height*4);
		glReadPixels(rect.x, windowSize.y - rect.height - rect.y, rect.width, rect.height, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer.data());

		// Les pixels sont retournés, nous devons envoyer les pixels par rangée
		for (unsigned int i = 0; i < rect.height; ++i)
			image->Update(&m_buffer[rect.width*4*i], Boxui(dstPos.x, rect.height - i - 1, dstPos.z, rect.width, 1, 1), rect.width);

		if (m_context != currentContext)
		{
			if (currentContext)
			{
				if (!currentContext->SetActive(true))
					NazaraWarning("Failed to reset old context");
			}
			else
				m_context->SetActive(false);
		}

		return true;
	}

	bool RenderWindow::Create(VideoMode mode, const String& title, WindowStyleFlags style, const ContextParameters& parameters)
	{
		m_parameters = parameters;
		return Window::Create(mode, title, style);
	}

	bool RenderWindow::Create(WindowHandle handle, const ContextParameters& parameters)
	{
		m_parameters = parameters;
		return Window::Create(handle);
	}

=======
>>>>>>> VulkanRenderer: Add RenderWindow wrapper
	void RenderWindow::Display()
	{
		if (m_framerateLimit > 0)
		{
			int remainingTime = 1000/static_cast<int>(m_framerateLimit) - static_cast<int>(m_clock.GetMilliseconds());
			if (remainingTime > 0)
				Thread::Sleep(remainingTime);

			m_clock.Restart();
		}
	}

	void RenderWindow::EnableVerticalSync(bool enabled)
	{
<<<<<<< HEAD
		if (m_context)
		{
			if (!m_context->SetActive(true))
			{
				NazaraError("Failed to activate context");
				return;
			}

			m_context->EnableVerticalSync(enabled);
		}
		else
			NazaraError("No context");
	}

	RenderTargetParameters RenderWindow::GetParameters() const
	{
		if (m_context)
		{
			const ContextParameters& parameters = m_context->GetParameters();
			return RenderTargetParameters(parameters.antialiasingLevel, parameters.depthBits, parameters.stencilBits);
		}
		else
		{
			NazaraError("Window not created/context not initialized");
			return RenderTargetParameters();
		}
	}

	Vector2ui RenderWindow::GetSize() const
	{
		return Window::GetSize();
	}

	bool RenderWindow::IsRenderable() const
	{
		return m_impl != nullptr; // Si m_impl est valide, alors m_context l'est aussi
	}

	bool RenderWindow::IsValid() const
	{
		return m_impl != nullptr;
	}

	void RenderWindow::SetFramerateLimit(unsigned int limit)
	{
		m_framerateLimit = limit;
	}

	ContextParameters RenderWindow::GetContextParameters() const
	{
		if (m_context)
			return m_context->GetParameters();
		else
		{
			NazaraError("Window not created/context not initialized");
			return ContextParameters();
		}
	}

	bool RenderWindow::HasContext() const
	{
		return true;
	}

	bool RenderWindow::Activate() const
	{
		if (m_context->SetActive(true))
		{
			glDrawBuffer((m_parameters.doubleBuffered) ? GL_BACK : GL_FRONT);
			return true;
		}
		else
		{
			NazaraError("Failed to activate window's context");
			return false;
		}
	}

	void RenderWindow::EnsureTargetUpdated() const
	{
		// Rien à faire
=======
		///TODO
>>>>>>> VulkanRenderer: Add RenderWindow wrapper
	}

	bool RenderWindow::OnWindowCreated()
	{
		auto surface = Renderer::GetRendererImpl()->CreateRenderSurfaceImpl();
		if (!surface->Create(GetHandle()))
		{
			NazaraError("Failed to create render surface: " + Error::GetLastError());
			return false;
		}

		auto impl = Renderer::GetRendererImpl()->CreateRenderWindowImpl();
		if (!impl->Create(surface.get(), Vector2ui(GetWidth(), GetHeight()), m_parameters))
		{
			NazaraError("Failed to create render window implementation: " + Error::GetLastError());
			return false;
		}

		m_impl = std::move(impl);
		m_surface = std::move(surface);

		m_clock.Restart();

		return true;
	}

	void RenderWindow::OnWindowDestroy()
	{
		m_impl.reset();
		m_surface.reset();
	}

	void RenderWindow::OnWindowResized()
	{
	}
}
