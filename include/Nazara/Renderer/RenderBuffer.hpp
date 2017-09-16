// Copyright (C) 2017 Jérôme Leclercq
<<<<<<< HEAD
// This file is part of the "Nazara Engine - Renderer module"
=======
// This file is part of the "Nazara Engine - Utility module"
>>>>>>> Vulkan/RenderBuffer: WIP
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_RENDERBUFFER_HPP
#define NAZARA_RENDERBUFFER_HPP

<<<<<<< HEAD
#include <Nazara/Prerequisites.hpp>
#include <Nazara/Core/ObjectLibrary.hpp>
#include <Nazara/Core/ObjectRef.hpp>
#include <Nazara/Core/RefCounted.hpp>
#include <Nazara/Core/Signal.hpp>
#include <Nazara/Renderer/Config.hpp>
#include <Nazara/Utility/Enums.hpp>

namespace Nz
{
	class RenderBuffer;

	using RenderBufferConstRef = ObjectRef<const RenderBuffer>;
	using RenderBufferLibrary = ObjectLibrary<RenderBuffer>;
	using RenderBufferRef = ObjectRef<RenderBuffer>;

	class NAZARA_RENDERER_API RenderBuffer : public RefCounted
	{
		friend RenderBufferLibrary;
		friend class Renderer;

		public:
			RenderBuffer();
			RenderBuffer(const RenderBuffer&) = delete;
			RenderBuffer(RenderBuffer&&) = delete;
			~RenderBuffer();

			bool Create(PixelFormatType format, unsigned int width, unsigned int height);
			void Destroy();

			unsigned int GetHeight() const;
			PixelFormatType GetFormat() const;
			unsigned int GetWidth() const;

			// Fonctions OpenGL
			unsigned int GetOpenGLID() const;

			bool IsValid() const;

			RenderBuffer& operator=(const RenderBuffer&) = delete;
			RenderBuffer& operator=(RenderBuffer&&) = delete;

			template<typename... Args> static RenderBufferRef New(Args&&... args);

			// Signals:
			NazaraSignal(OnRenderBufferDestroy, const RenderBuffer* /*renderBuffer*/);
			NazaraSignal(OnRenderBufferRelease, const RenderBuffer* /*renderBuffer*/);

		private:
			static bool Initialize();
			static void Uninitialize();

			PixelFormatType m_pixelFormat;
			unsigned int m_height;
			unsigned int m_id;
			unsigned int m_width;

			static RenderBufferLibrary::LibraryMap s_library;
	};
=======
#include <Nazara/Renderer/Config.hpp>
#include <Nazara/Utility/AbstractBuffer.hpp>
#include <Nazara/Utility/SoftwareBuffer.hpp>

namespace Nz
{
	class NAZARA_RENDERER_API RenderBuffer : public AbstractBuffer
	{
		public:
			RenderBuffer() = default;
			~RenderBuffer() = default;

			virtual bool Fill(const void* data, UInt32 offset, UInt32 size) = 0;

			bool Initialize(UInt32 size, BufferUsageFlags usage) override;

			DataStorage GetStorage() const override;

			virtual void* Map(BufferAccess access, UInt32 offset = 0, UInt32 size = 0) = 0;
			virtual bool Unmap() = 0;

		private:
			SoftwareBuffer m_softwareBuffer;
	};

>>>>>>> Vulkan/RenderBuffer: WIP
}

#include <Nazara/Renderer/RenderBuffer.inl>

#endif // NAZARA_RENDERBUFFER_HPP
