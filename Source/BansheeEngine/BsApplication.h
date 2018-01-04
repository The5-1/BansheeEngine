//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsPrerequisites.h"
#include "BsCoreApplication.h"
#include "Utility/BsEvent.h"

namespace bs
{
	/** @addtogroup Application-Engine
	 *  @{
	 */

	/**	Primary entry point for Banshee engine. Handles startup and shutdown. */
	class BS_EXPORT Application : public CoreApplication
	{
	private:
		/** 
		 * Builds the start-up descriptor structure, filling out the provided parameters and using the default values
		 * for the rest. 
		 */
		static START_UP_DESC buildStartUpDesc(VideoMode videoMode, const String& title, bool fullscreen);
	public:
		Application(const START_UP_DESC& desc);
		virtual ~Application();

		/** Starts the Banshee engine. If using a custom Application system, provide it as a template parameter. */
		template<class T = Application>
		static void startUp(VideoMode videoMode, const String& title, bool fullscreen)
		{
			START_UP_DESC desc = buildStartUpDesc(videoMode, title, fullscreen);
			CoreApplication::startUp<T>(desc);
		}

		/** Starts the Banshee engine. If using a custom Application system, provide it as a template parameter. */
		template<class T = Application>
		static void startUp(const START_UP_DESC& desc)
		{
			CoreApplication::startUp<T>(desc);
		}

		/**	Returns the absolute path to the builtin managed engine assembly file. */
		Path getEngineAssemblyPath() const;

		/**	Returns the absolute path to the game managed assembly file. */
		Path getGameAssemblyPath() const;

		/**	Returns the absolute path to the folder where script assemblies are located in. */
		virtual Path getScriptAssemblyFolder() const;

	protected:
		/** @copydoc Module::onStartUp */
		void onStartUp() override;

		/** @copydoc Module::onShutDown */
		void onShutDown() override;

		/** @copydoc CoreApplication::preUpdate */
		void preUpdate() override;

		/** @copydoc CoreApplication::postUpdate */
		void postUpdate() override;

		/** @copydoc CoreApplication::startUpRenderer */
		void startUpRenderer() override;

		/** @copydoc CoreApplication::getShaderIncludeHandler */
		SPtr<IShaderIncludeHandler> getShaderIncludeHandler() const override;

		/**	Loads the script system and all script libraries. */
		virtual void loadScriptSystem();

		/**	Unloads script libraries and shuts down the script system. */
		virtual void unloadScriptSystem();

		/**	Returns the absolute path to the folder where built-in assemblies are located in. */
		virtual Path getBuiltinAssemblyFolder() const;

		DynLib* mMonoPlugin;
		DynLib* mSBansheeEnginePlugin;
	};

	/** Easy way to access Application. */
	BS_EXPORT Application& gApplication();

	/** @} */
}