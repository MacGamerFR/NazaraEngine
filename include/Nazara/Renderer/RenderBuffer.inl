// Copyright (C) 2017 Jérôme Leclercq
<<<<<<< HEAD
// This file is part of the "Nazara Engine - Renderer module"
=======
// This file is part of the "Nazara Engine - Utility module"
>>>>>>> Vulkan/RenderBuffer: WIP
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <memory>
#include <Nazara/Renderer/Debug.hpp>

namespace Nz
{
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
}

#include <Nazara/Renderer/DebugOff.hpp>
