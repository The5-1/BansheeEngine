//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsCorePrerequisites.h"
#include "Utility/BsModule.h"
#include "Error/BsException.h"
#include "RenderAPI/BsGpuProgram.h"

namespace bs 
{
	/** @addtogroup RenderAPI-Internal
	 *  @{
	 */

	/**
	 * Manager responsible for creating GPU programs. It will automatically try to find the appropriate handler for a 
	 * specific GPU program language and create the program if possible.
	 *
	 * @note	Sim thread only.
	 */
	class BS_CORE_EXPORT GpuProgramManager : public Module<GpuProgramManager>
	{
	public:
		/** @copydoc GpuProgram::create */
		SPtr<GpuProgram> create(const GPU_PROGRAM_DESC& desc);

		/**
		 * Creates a completely empty and uninitialized GpuProgram. Should only be used for specific purposes, like 
		 * deserialization, as it requires additional manual initialization that is not required normally.
		 */
		SPtr<GpuProgram> createEmpty(const String& language, GpuProgramType type);
	};

	namespace ct
	{
	/** Factory responsible for creating GPU programs of a certain type. */
	class BS_CORE_EXPORT GpuProgramFactory
	{
	public:
        GpuProgramFactory() {}
		virtual ~GpuProgramFactory() { }

		/**	Returns GPU program language this factory is capable creating GPU programs from. */
		virtual const String& getLanguage() const = 0;

		/** @copydoc GpuProgram::create */
		virtual SPtr<GpuProgram> create(const GPU_PROGRAM_DESC& desc, GpuDeviceFlags deviceMask = GDF_DEFAULT) = 0;

		/** @copydoc bs::GpuProgramManager::createEmpty */
		virtual SPtr<GpuProgram> create(GpuProgramType type, GpuDeviceFlags deviceMask = GDF_DEFAULT) = 0;
	};

	/**
	 * Manager responsible for creating GPU programs. It will automatically	try to find the appropriate handler for a 
	 * specific GPU program language and create the program if possible.
	 *
	 * @note	Core thread only.
	 */
	class BS_CORE_EXPORT GpuProgramManager : public Module<GpuProgramManager>
	{
	public:
		GpuProgramManager();
		virtual ~GpuProgramManager();

		/**
		 * Registers a new factory that is able to create GPU programs for a certain language. If any other factory for the
		 * same language exists, it will overwrite it.
		 */
		void addFactory(GpuProgramFactory* factory);

		/**
		 * Unregisters a GPU program factory, essentially making it not possible to create GPU programs using the language 
		 * the factory supported.
		 */
		void removeFactory(GpuProgramFactory* factory);

		/** Query if a GPU program language is supported (for example "hlsl", "glsl"). */
		bool isLanguageSupported(const String& lang);

		/** @copydoc GpuProgram::create */
		SPtr<GpuProgram> create(const GPU_PROGRAM_DESC& desc, GpuDeviceFlags deviceMask = GDF_DEFAULT);

	protected:
		friend class bs::GpuProgram;

		/**
		 * Creates a GPU program without initializing it.
		 *
		 * @see		create
		 */
		SPtr<GpuProgram> createInternal(const GPU_PROGRAM_DESC& desc, GpuDeviceFlags deviceMask = GDF_DEFAULT);

		/** Attempts to find a factory for the specified language. Returns null if it cannot find one. */
		GpuProgramFactory* getFactory(const String& language);

	protected:
		typedef Map<String, GpuProgramFactory*> FactoryMap;

		FactoryMap mFactories;
		GpuProgramFactory* mNullFactory; /**< Factory for dealing with GPU programs that can't be created. */
	};
	}
	/** @} */
}