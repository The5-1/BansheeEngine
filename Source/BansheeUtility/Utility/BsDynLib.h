//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "Prerequisites/BsPrerequisitesUtil.h"

#if BS_PLATFORM == BS_PLATFORM_WIN32
	struct HINSTANCE__;
	typedef struct HINSTANCE__* hInstance;
#endif

namespace bs 
{
	/** @addtogroup General
	 *  @{
	 */

#if BS_PLATFORM == BS_PLATFORM_WIN32
#    define DYNLIB_HANDLE hInstance
#    define DYNLIB_LOAD( a ) LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#    define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#    define DYNLIB_UNLOAD( a ) !FreeLibrary( a )

#elif BS_PLATFORM == BS_PLATFORM_LINUX || BS_PLATFORM == BS_PLATFORM_OSX
#    define DYNLIB_HANDLE void*
#    define DYNLIB_LOAD( a ) dlopen( a, RTLD_LAZY | RTLD_GLOBAL)
#    define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#    define DYNLIB_UNLOAD( a ) dlclose( a )

#endif

    /** Class that holds data about a dynamic library. */
	class BS_UTILITY_EXPORT DynLib
    {
    public:
		/** Platform-specific file extension for a dynamic library (e.g. "dll"). */
		static const char* EXTENSION;

		/** Platform-specific name suffix for a dynamic library (e.g. "lib" on Unix) */
		static const char* PREFIX;

		/** Constructs the dynamic library object and loads the library with the specified name. */
		DynLib(const String& name);
        ~DynLib();

		/** Loads the library. Does nothing if library is already loaded. */
        void load();

		/** Unloads the library. Does nothing if library is not loaded. */
        void unload();

		/** Get the name of the library. */
		const String& getName() const { return mName; }

        /**
		 * Returns the address of the given symbol from the loaded library.
		 *
		 * @param[in] strName	The name of the symbol to search for.
         * @return				If the function succeeds, the returned value is a handle to the symbol. Otherwise null.
         */
        void* getSymbol(const String& strName) const;

	protected:
		friend class DynLibManager;

		/** Gets the last loading error. */
        String dynlibError();

    protected:
		String mName;
        DYNLIB_HANDLE mHandle;
    };

	/** @} */
}
