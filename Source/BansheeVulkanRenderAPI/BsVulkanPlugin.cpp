//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsVulkanPrerequisites.h"
#include "Managers/BsVulkanRenderAPIFactory.h"

namespace bs
{
	extern "C" BS_PLUGIN_EXPORT const char* getPluginName()
	{
		return ct::SystemName;
	}
}