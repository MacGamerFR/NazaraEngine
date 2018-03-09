<<<<<<< HEAD
// Copyright (C) 2017 Jérôme Leclercq
=======
// Copyright (C) 2015 Jérôme Leclercq
>>>>>>> Vulkan/RenderBuffer: WIP
// This file is part of the "Nazara Engine - Renderer module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Renderer/RenderBuffer.hpp>
<<<<<<< HEAD
<<<<<<< HEAD
#include <Nazara/Core/Error.hpp>
#include <Nazara/Renderer/Context.hpp>
#include <Nazara/Renderer/OpenGL.hpp>
#include <Nazara/Utility/PixelFormat.hpp>
=======
>>>>>>> Vulkan/RenderBuffer: WIP
=======
#include <Nazara/Core/Error.hpp>
>>>>>>> Add buffer support
#include <Nazara/Renderer/Debug.hpp>

namespace Nz
{
<<<<<<< HEAD
<<<<<<< HEAD
	RenderBuffer::RenderBuffer() :
	m_id(0)
	{
	}

	RenderBuffer::~RenderBuffer()
	{
		OnRenderBufferRelease(this);

		Destroy();
	}

	bool RenderBuffer::Create(PixelFormatType format, unsigned int width, unsigned int height)
	{
		Destroy();

		#if NAZARA_RENDERER_SAFE
		if (width == 0 || height == 0)
		{
			NazaraError("Invalid size");
			return false;
		}

		if (!PixelFormat::IsValid(format))
		{
			NazaraError("Invalid pixel format");
			return false;
		}
		#endif

		OpenGL::Format openglFormat;
		if (!OpenGL::TranslateFormat(format, &openglFormat, OpenGL::FormatType_RenderBuffer))
		{
			NazaraError("Failed to translate pixel format \"" + PixelFormat::GetName(format) + "\" into OpenGL format");
			return false;
		}

		GLuint renderBuffer = 0;

		glGenRenderbuffers(1, &renderBuffer);
		if (!renderBuffer)
		{
			NazaraError("Failed to create renderbuffer");
			return false;
		}

		GLint previous;
		glGetIntegerv(GL_RENDERBUFFER_BINDING, &previous);

		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, openglFormat.internalFormat, width, height);

		if (previous != 0)
			glBindRenderbuffer(GL_RENDERBUFFER, previous);

		m_pixelFormat = format;
		m_height = height;
		m_id = renderBuffer;
		m_width = width;

		return true;
	}

	void RenderBuffer::Destroy()
	{
		if (m_id)
		{
			OnRenderBufferDestroy(this);

			Context::EnsureContext();

			GLuint renderBuffer = m_id;
			glDeleteRenderbuffers(1, &renderBuffer); // Les Renderbuffers sont partagés entre les contextes: Ne posera pas de problème
			m_id = 0;
		}
	}

	unsigned int RenderBuffer::GetHeight() const
	{
		return m_height;
	}

	PixelFormatType RenderBuffer::GetFormat() const
	{
		return m_pixelFormat;
	}

	unsigned int RenderBuffer::GetWidth() const
	{
		return m_width;
	}

	unsigned int RenderBuffer::GetOpenGLID() const
	{
		return m_id;
	}

	bool RenderBuffer::IsValid() const
	{
		return m_id != 0;
	}

	bool RenderBuffer::Initialize()
	{
		if (!RenderBufferLibrary::Initialize())
		{
			NazaraError("Failed to initialise library");
			return false;
		}

		return true;
	}

	void RenderBuffer::Uninitialize()
	{
		RenderBufferLibrary::Uninitialize();
	}

	RenderBufferLibrary::LibraryMap RenderBuffer::s_library;
=======
=======
	bool RenderBuffer::Fill(const void* data, UInt32 offset, UInt32 size)
	{
		if (m_softwareBuffer.Fill(data, offset, size))
		{
			for (auto& bufferPair : m_hardwareBuffers)
				bufferPair.second.synchronized = false;

			return true;
		}
		else
			return false;
	}

>>>>>>> Add buffer support
	bool RenderBuffer::Initialize(UInt32 size, BufferUsageFlags usage)
	{
		m_size = size;
		m_softwareBuffer.Initialize(size, usage);

		return true;
	}

	AbstractBuffer* RenderBuffer::GetHardwareBuffer(RenderDevice* device)
	{
		auto it = m_hardwareBuffers.find(device);
		if (it == m_hardwareBuffers.end())
			return nullptr;

		return it->second.buffer.get();
	}

	DataStorage RenderBuffer::GetStorage() const
	{
		return DataStorage::DataStorage_Hardware;
	}
<<<<<<< HEAD
>>>>>>> Vulkan/RenderBuffer: WIP
=======

	void* RenderBuffer::Map(BufferAccess access, UInt32 offset, UInt32 size)
	{
		if (void* ptr = m_softwareBuffer.Map(access, offset, size))
		{
			if (access != BufferAccess_ReadOnly)
			{
				for (auto& bufferPair : m_hardwareBuffers)
					bufferPair.second.synchronized = false;
			}

			return ptr;
		}
		else
			return nullptr;
	}

	bool RenderBuffer::Unmap()
	{
		return m_softwareBuffer.Unmap();
	}

	bool RenderBuffer::Synchronize(RenderDevice* device)
	{
		auto it = m_hardwareBuffers.find(device);
		if (it == m_hardwareBuffers.end())
		{
			HardwareBuffer hwBuffer;
			hwBuffer.buffer = device->InstantiateBuffer(m_parent, m_type);
			if (!hwBuffer.buffer->Initialize(m_size, m_usage))
			{
				NazaraError("Failed to initialize hardware buffer");
				return false;
			}

			it = m_hardwareBuffers.emplace(device, std::move(hwBuffer)).first;
		}

		HardwareBuffer& hwBuffer = it->second;
		if (hwBuffer.synchronized)
			return true;

		return hwBuffer.buffer->Fill(m_softwareBuffer.GetData(), 0, m_size);
	}
>>>>>>> Add buffer support
}
