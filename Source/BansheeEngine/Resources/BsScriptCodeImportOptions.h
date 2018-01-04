//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsPrerequisites.h"
#include "Importer/BsImportOptions.h"
#include "Resources/BsScriptCode.h"

namespace bs
{
	/** @addtogroup Resources-Engine
	 *  @{
	 */

	/** Contains import options you may use to control how is a file containing script source code importer. */
	class BS_EXPORT ScriptCodeImportOptions : public ImportOptions
	{
	public:
		ScriptCodeImportOptions();

		/**	Sets whether the script is editor-only or a normal game script. */
		void setEditorScript(bool editorScript) { mEditorScript = editorScript; }

		/**	Checks whether the script is editor-only or a normal game script. */
		bool isEditorScript() const { return mEditorScript; }

		/** Creates a new import options object that allows you to customize how is script code imported. */
		static SPtr<ScriptCodeImportOptions> create();

		/************************************************************************/
		/* 								SERIALIZATION                      		*/
		/************************************************************************/
	public:
		friend class ScriptCodeImportOptionsRTTI;
		static RTTITypeBase* getRTTIStatic();
		RTTITypeBase* getRTTI() const override;

	private:
		bool mEditorScript;
	};

	/** @} */
}