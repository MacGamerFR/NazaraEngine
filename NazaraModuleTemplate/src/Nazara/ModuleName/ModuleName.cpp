// Copyright (C) YEAR AUTHORS
// This file is part of the "Nazara Engine - Module name"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/ModuleName/ModuleName.hpp>
#include <Nazara/Core/CallOnExit.hpp>
#include <Nazara/Core/Core.hpp>
#include <Nazara/Core/Error.hpp>
#include <Nazara/Core/Log.hpp>
#include <Nazara/ModuleName/Config.hpp>
#include <Nazara/ModuleName/Debug.hpp>

namespace Nz
{
<<<<<<< HEAD:NazaraModuleTemplate/src/Nazara/ModuleName/ModuleName.cpp
	bool ModuleName::Initialize()
=======
	Vk::Instance& Vulkan::GetInstance()
	{
		return s_instance;
	}

	bool Vulkan::Initialize()
>>>>>>> Vulkan/Core: Add loader and instance initialization:src/Nazara/Vulkan/Vulkan.cpp
	{
		if (s_moduleReferenceCounter > 0)
		{
			s_moduleReferenceCounter++;
			return true; // Already initialized
		}

		// Initialize module dependencies
		if (!Core::Initialize())
		{
			NazaraError("Failed to initialize core module");
			return false;
		}

		s_moduleReferenceCounter++;

		CallOnExit onExit(ModuleName::Uninitialize);

		// Initialize module here
		if (!Vk::Loader::Initialize())
		{
			NazaraError("Failed to load Vulkan API, it may be not installed on your system");
			return false;
		}

		String appName = "Another application made with Nazara Engine";
		String engineName = "Nazara Engine - Vulkan Renderer";
		UInt32 apiVersion = VK_MAKE_VERSION(1, 0, 8);
		UInt32 appVersion = VK_MAKE_VERSION(1, 0, 0);
		UInt32 engineVersion = VK_MAKE_VERSION(1, 0, 0);

		s_initializationParameters.GetStringParameter("VkAppInfo_OverrideApplicationName", &appName);
		s_initializationParameters.GetStringParameter("VkAppInfo_OverrideEngineName", &engineName);

		int iParam;

		if (s_initializationParameters.GetIntegerParameter("VkAppInfo_OverrideAPIVersion", &iParam))
			apiVersion = iParam;

		if (s_initializationParameters.GetIntegerParameter("VkAppInfo_OverrideApplicationVersion", &iParam))
			appVersion = iParam;

		if (s_initializationParameters.GetIntegerParameter("VkAppInfo_OverrideEngineVersion", &iParam))
			engineVersion = iParam;

		VkApplicationInfo appInfo = {
			VK_STRUCTURE_TYPE_APPLICATION_INFO,
			nullptr,
			appName.GetConstBuffer(),
			appVersion,
			engineName.GetConstBuffer(),
			engineVersion,
			apiVersion
		};

		VkInstanceCreateFlags createFlags = 0;

		if (s_initializationParameters.GetIntegerParameter("VkInstanceInfo_OverrideCreateFlags", &iParam))
			createFlags = static_cast<VkInstanceCreateFlags>(iParam);

		std::vector<const char*> enabledLayers;
		std::vector<const char*> enabledExtensions;

		bool bParam;
		if (!s_initializationParameters.GetBooleanParameter("VkInstanceInfo_OverrideEnabledExtensions", &bParam) || !bParam)
		{
			enabledExtensions.push_back("VK_KHR_surface");

			#ifdef VK_USE_PLATFORM_ANDROID_KHR
			enabledExtensions.push_back("VK_KHR_android_surface");
			#endif

			#ifdef VK_USE_PLATFORM_MIR_KHR
			enabledExtensions.push_back("VK_KHR_mir_surface");
			#endif

			#ifdef VK_USE_PLATFORM_XCB_KHR
			enabledExtensions.push_back("VK_KHR_xcb_surface");
			#endif

			#ifdef VK_USE_PLATFORM_XLIB_KHR
			enabledExtensions.push_back("VK_KHR_xlib_surface");
			#endif

			#ifdef VK_USE_PLATFORM_WAYLAND_KHR
			enabledExtensions.push_back("VK_KHR_wayland_surface");
			#endif

			#ifdef VK_USE_PLATFORM_WIN32_KHR
			enabledExtensions.push_back("VK_KHR_win32_surface");
			#endif
		}

		std::vector<String> additionalExtensions; // Just to keep the String alive
		if (s_initializationParameters.GetIntegerParameter("VkInstanceInfo_EnabledExtensionCount", &iParam))
		{
			for (int i = 0; i < iParam; ++i)
			{
				Nz::String parameterName = "VkInstanceInfo_EnabledExtension" + String::Number(i);
				Nz::String extension;
				if (s_initializationParameters.GetStringParameter(parameterName, &extension))
				{
					additionalExtensions.emplace_back(std::move(extension));
					enabledExtensions.push_back(additionalExtensions.back().GetConstBuffer());
				}
				else
					NazaraWarning("Parameter " + parameterName + " expected");
			}
		}

		VkInstanceCreateInfo instanceInfo = {
			VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			nullptr,
			createFlags,
			&appInfo,
			UInt32(enabledLayers.size()),
			enabledLayers.data(),
			UInt32(enabledExtensions.size()),
			enabledExtensions.data()
		};
		
		if (!s_instance.Create(instanceInfo))
		{
			NazaraError("Failed to create instance");
			return false;
		}

		onExit.Reset();

		NazaraNotice("Initialized: ModuleName module");
		return true;
	}

	bool ModuleName::IsInitialized()
	{
		return s_moduleReferenceCounter != 0;
	}

<<<<<<< HEAD:NazaraModuleTemplate/src/Nazara/ModuleName/ModuleName.cpp
	void ModuleName::Uninitialize()
=======
	void Vulkan::SetParameters(const ParameterList& parameters)
	{
		s_initializationParameters = parameters;
	}

	void Vulkan::Uninitialize()
>>>>>>> Vulkan/Core: Add loader and instance initialization:src/Nazara/Vulkan/Vulkan.cpp
	{
		if (s_moduleReferenceCounter != 1)
		{
			// Either the module is not initialized, either it was initialized multiple times
			if (s_moduleReferenceCounter > 1)
				s_moduleReferenceCounter--;

			return;
		}

		s_moduleReferenceCounter = 0;

		// Uninitialize module here
		s_instance.Destroy();

		Vk::Loader::Uninitialize();

		NazaraNotice("Uninitialized: ModuleName module");

		// Free module dependencies
		Core::Uninitialize();
	}

<<<<<<< HEAD:NazaraModuleTemplate/src/Nazara/ModuleName/ModuleName.cpp
	unsigned int ModuleName::s_moduleReferenceCounter = 0;	
=======
	Vk::Instance Vulkan::s_instance;
	ParameterList Vulkan::s_initializationParameters;
	unsigned int Vulkan::s_moduleReferenceCounter = 0;	
>>>>>>> Vulkan/Core: Add loader and instance initialization:src/Nazara/Vulkan/Vulkan.cpp
}

