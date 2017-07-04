<<<<<<< HEAD
// Copyright (C) 2017 Jérôme Leclercq
=======
// Copyright (C) 2016 Jérôme Leclercq
>>>>>>> VulkanRenderer: Add RenderWindow wrapper
// This file is part of the "Nazara Engine - Renderer module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_RENDERWINDOW_HPP
#define NAZARA_RENDERWINDOW_HPP

#include <Nazara/Prerequisites.hpp>
#include <Nazara/Core/Clock.hpp>
#include <Nazara/Math/Rect.hpp>
#include <Nazara/Math/Vector3.hpp>
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include <Nazara/Renderer/Config.hpp>
#include <Nazara/Renderer/ContextParameters.hpp>
#include <Nazara/Renderer/RenderTarget.hpp>
#include <Nazara/Platform/Window.hpp>
=======
#include <Nazara/Utility/Window.hpp>
>>>>>>> Add new Renderer architecture (far from complete)
#include <vector>

namespace Nz
{
	class AbstractImage;
	class Context;

	class NAZARA_RENDERER_API RenderWindow : public RenderTarget, public Window
	{
		public:
			RenderWindow() = default;
			RenderWindow(VideoMode mode, const String& title, WindowStyleFlags style = WindowStyle_Default, const ContextParameters& parameters = ContextParameters());
			explicit RenderWindow(WindowHandle handle, const ContextParameters& parameters = ContextParameters());
=======
=======
#include <Nazara/Renderer/RenderSurface.hpp>
>>>>>>> Commit WIP about RenderSurface
#include <Nazara/Renderer/RenderWindowImpl.hpp>
#include <Nazara/Renderer/RenderWindowParameters.hpp>
#include <Nazara/Utility/Window.hpp>
#include <memory>

namespace Nz
{
	class NAZARA_RENDERER_API RenderWindow : public Window
	{
		public:
			inline RenderWindow();
			inline RenderWindow(VideoMode mode, const String& title, UInt32 style = WindowStyle_Default, const RenderWindowParameters& parameters = RenderWindowParameters());
			inline RenderWindow(WindowHandle handle, const RenderWindowParameters& parameters = RenderWindowParameters());
<<<<<<< HEAD
>>>>>>> VulkanRenderer: Add RenderWindow wrapper
			RenderWindow(const RenderWindow&) = delete;
			RenderWindow(RenderWindow&&) = delete; ///TODO
			virtual ~RenderWindow();

<<<<<<< HEAD
			bool CopyToImage(AbstractImage* image, const Vector3ui& dstPos = Vector3ui(0U)) const;
			bool CopyToImage(AbstractImage* image, const Rectui& rect, const Vector3ui& dstPos = Vector3ui(0U)) const;

			bool Create(VideoMode mode, const String& title, WindowStyleFlags style = WindowStyle_Default, const ContextParameters& parameters = ContextParameters());
			bool Create(WindowHandle handle, const ContextParameters& parameters = ContextParameters());
=======
			inline bool Create(VideoMode mode, const String& title, UInt32 style = WindowStyle_Default, const RenderWindowParameters& parameters = RenderWindowParameters());
=======

			inline bool Create(VideoMode mode, const String& title, WindowStyleFlags style = WindowStyle_Default, const RenderWindowParameters& parameters = RenderWindowParameters());
>>>>>>> Remove unused code
			inline bool Create(WindowHandle handle, const RenderWindowParameters& parameters = RenderWindowParameters());
>>>>>>> VulkanRenderer: Add RenderWindow wrapper

			void Display();

			void EnableVerticalSync(bool enabled);

<<<<<<< HEAD
			RenderTargetParameters GetParameters() const override;
			Vector2ui GetSize() const override;
=======
			inline RenderWindowImpl* GetImpl();
>>>>>>> VulkanRenderer: Add RenderWindow wrapper

			inline bool IsValid() const;

			inline void SetFramerateLimit(unsigned int limit);

			RenderWindow& operator=(const RenderWindow&) = delete;
			RenderWindow& operator=(RenderWindow&&) = delete; ///TODO

		protected:
			bool OnWindowCreated() override;
			void OnWindowDestroy() override;
			void OnWindowResized() override;

		private:
			std::unique_ptr<RenderWindowImpl> m_impl;
			Clock m_clock;
			std::unique_ptr<RenderSurface> m_surface;
			RenderWindowParameters m_parameters;
			unsigned int m_framerateLimit;
	};
}

#include <Nazara/Renderer/RenderWindow.inl>

#endif // NAZARA_RENDERWINDOW_HPP
