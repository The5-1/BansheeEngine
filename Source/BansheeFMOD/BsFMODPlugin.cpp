//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsFMODPrerequisites.h"
#include "Audio/BsAudioManager.h"
#include "BsFMODAudio.h"
#include "BsFMODImporter.h"
#include "Importer/BsImporter.h"

namespace bs
{
	class FMODFactory : public AudioFactory
	{
	public:
		void startUp() override
		{
			Audio::startUp<FMODAudio>();
		}

		void shutDown() override
		{
			Audio::shutDown();
		}
	};

	/**	Returns a name of the plugin. */
	extern "C" BS_PLUGIN_EXPORT const char* getPluginName()
	{
		static const char* pluginName = "BansheeFMOD";
		return pluginName;
	}

	/**	Entry point to the plugin. Called by the engine when the plugin is loaded. */
	extern "C" BS_PLUGIN_EXPORT void* loadPlugin()
	{
		FMODImporter* importer = bs_new<FMODImporter>();
		Importer::instance()._registerAssetImporter(importer);

		return bs_new<FMODFactory>();
	}

	/**	Exit point of the plugin. Called by the engine before the plugin is unloaded. */
	extern "C" BS_PLUGIN_EXPORT void unloadPlugin(FMODFactory* instance)
	{
		bs_delete(instance);
	}
}