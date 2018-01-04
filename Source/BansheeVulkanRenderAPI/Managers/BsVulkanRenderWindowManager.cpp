//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Managers/BsVulkanRenderWindowManager.h"

#if BS_PLATFORM == BS_PLATFORM_WIN32
#include "Win32/BsWin32RenderWindow.h"
#elif BS_PLATFORM == BS_PLATFORM_LINUX
#include "Linux/BsLinuxRenderWindow.h"
#endif

namespace bs 
{
	VulkanRenderWindowManager::VulkanRenderWindowManager()
	{ }

	SPtr<RenderWindow> VulkanRenderWindowManager::createImpl(RENDER_WINDOW_DESC& desc, UINT32 windowId, const SPtr<RenderWindow>& parentWindow)
	{
		if(parentWindow != nullptr)
		{
			UINT64 hWnd;
			parentWindow->getCustomAttribute("WINDOW", &hWnd);
			desc.platformSpecific["parentWindowHandle"] = toString(hWnd);
		}

		// Create the window
#if BS_PLATFORM == BS_PLATFORM_WIN32
		Win32RenderWindow* renderWindow = new (bs_alloc<Win32RenderWindow>()) Win32RenderWindow(desc, windowId);
		return bs_core_ptr<Win32RenderWindow>(renderWindow);
#elif BS_PLATFORM == BS_PLATFORM_LINUX
		LinuxRenderWindow* renderWindow = new (bs_alloc<LinuxRenderWindow>()) LinuxRenderWindow(desc, windowId);
		return bs_core_ptr<LinuxRenderWindow>(renderWindow);
#endif
	}

	namespace ct
	{
		VulkanRenderWindowManager::VulkanRenderWindowManager(VulkanRenderAPI& renderAPI)
		:mRenderAPI(renderAPI)
	{ }

	SPtr<RenderWindow> VulkanRenderWindowManager::createInternal(RENDER_WINDOW_DESC& desc, UINT32 windowId)
	{
		// Create the window
#if BS_PLATFORM == BS_PLATFORM_WIN32
		Win32RenderWindow* renderWindow =
			new (bs_alloc<Win32RenderWindow>()) Win32RenderWindow(desc, windowId, mRenderAPI);
		SPtr<Win32RenderWindow> renderWindowPtr = bs_shared_ptr<Win32RenderWindow>(renderWindow);
#elif BS_PLATFORM == BS_PLATFORM_LINUX
		LinuxRenderWindow* renderWindow =
				new (bs_alloc<LinuxRenderWindow>()) LinuxRenderWindow(desc, windowId, mRenderAPI);
		SPtr<LinuxRenderWindow> renderWindowPtr = bs_shared_ptr<LinuxRenderWindow>(renderWindow);
#endif

		renderWindowPtr->_setThisPtr(renderWindowPtr);
		windowCreated(renderWindow);

		return renderWindowPtr;
	}
	}
}