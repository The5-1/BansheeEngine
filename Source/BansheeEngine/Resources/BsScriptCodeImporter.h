//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsPrerequisites.h"
#include "Importer/BsSpecificImporter.h"

namespace bs
{
	/** @addtogroup Resources-Engine-Internal
	 *  @{
	 */

	/**	Imports C# script source code files (.cs). */
	class BS_EXPORT ScriptCodeImporter : public SpecificImporter
	{
	public:
		ScriptCodeImporter();
		virtual ~ScriptCodeImporter();

		/** @copydoc SpecificImporter::isExtensionSupported */
		bool isExtensionSupported(const WString& ext) const override;

		/** @copydoc SpecificImporter::isMagicNumberSupported */
		bool isMagicNumberSupported(const UINT8* magicNumPtr, UINT32 numBytes) const override;

		/** @copydoc SpecificImporter::import */
		SPtr<Resource> import(const Path& filePath, SPtr<const ImportOptions> importOptions) override;

		/** @copydoc SpecificImporter::createImportOptions */
		SPtr<ImportOptions> createImportOptions() const override;

		static const WString DEFAULT_EXTENSION;
	};

	/** @} */
}