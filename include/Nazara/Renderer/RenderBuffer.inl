// Copyright (C) 2017 Jérôme Leclercq
<<<<<<< HEAD
// This file is part of the "Nazara Engine - Renderer module"
=======
// This file is part of the "Nazara Engine - Utility module"
>>>>>>> Vulkan/RenderBuffer: WIP
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Renderer/RenderBuffer.hpp>
#include <memory>
#include <Nazara/Renderer/Debug.hpp>

namespace Nz
{
<<<<<<< HEAD
<<<<<<< HEAD
	template<typename... Args>
	RenderBufferRef RenderBuffer::New(Args&&... args)
	{
		std::unique_ptr<RenderBuffer> object(new RenderBuffer(std::forward<Args>(args)...));
		object->SetPersistent(false);

		return object.release();
	}
=======
>>>>>>> Vulkan/RenderBuffer: WIP
=======
	inline RenderBuffer::RenderBuffer(Buffer* parent, BufferType type) :
	m_softwareBuffer(parent, type),
	m_parent(parent),
	m_type(type)
	{
	}
>>>>>>> Add buffer support
}

#include <Nazara/Renderer/DebugOff.hpp>
