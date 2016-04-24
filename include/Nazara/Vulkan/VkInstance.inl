// Copyright (C) 2016 Jérôme Leclercq
// This file is part of the "Nazara Engine - Vulkan"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Vulkan/VkInstance.hpp>
#include <Nazara/Core/Error.hpp>
#include <Nazara/Vulkan/Debug.hpp>

namespace Nz
{
	namespace Vk
	{
		inline Instance::Instance() :
		m_instance(nullptr)
		{
		}

		inline Instance::~Instance()
		{
			Destroy();
		}

		inline void Instance::Destroy()
		{
			if (m_instance)
				vkDestroyInstance(m_instance, (m_allocator.pfnAllocation) ? &m_allocator : nullptr);
		}

		inline PFN_vkVoidFunction Instance::GetDeviceProcAddr(VkDevice device, const char* name)
		{
			PFN_vkVoidFunction func = vkGetDeviceProcAddr(device, name);
			if (!func)
				NazaraError("Failed to get " + String(name) + " address");

			return func;
		}

		inline VkResult Instance::GetLastErrorCode() const
		{
			return m_lastErrorCode;
		}

		inline void Instance::GetPhysicalDeviceFeatures(VkPhysicalDevice device, VkPhysicalDeviceFeatures* features)
		{
			return vkGetPhysicalDeviceFeatures(device, features);
		}

		inline void Instance::GetPhysicalDeviceFormatProperties(VkPhysicalDevice device, VkFormat format, VkFormatProperties* formatProperties)
		{
			return vkGetPhysicalDeviceFormatProperties(device, format, formatProperties);
		}

		inline bool Instance::GetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* imageFormatProperties)
		{
			m_lastErrorCode = vkGetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, imageFormatProperties);
			if (m_lastErrorCode != VkResult::VK_SUCCESS)
			{
				NazaraError("Failed to get physical device image format properties");
				return false;
			}

			return true;
		}

		inline void Instance::GetPhysicalDeviceMemoryProperties(VkPhysicalDevice device, VkPhysicalDeviceMemoryProperties* memoryProperties)
		{
			return vkGetPhysicalDeviceMemoryProperties(device, memoryProperties);
		}

		inline void Instance::GetPhysicalDeviceProperties(VkPhysicalDevice device, VkPhysicalDeviceProperties* properties)
		{
			return vkGetPhysicalDeviceProperties(device, properties);
		}

		inline PFN_vkVoidFunction Instance::GetProcAddr(const char* name)
		{
			PFN_vkVoidFunction func = Loader::GetInstanceProcAddr(m_instance, name);
			if (!func)
				NazaraError("Failed to get " + String(name) + " address");
			
			return func;
		}
	}
}

#include <Nazara/Vulkan/DebugOff.hpp>
