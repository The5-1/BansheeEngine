//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Wrappers/BsScriptImportOptions.h"
#include "BsScriptMeta.h"
#include "BsMonoField.h"
#include "BsMonoClass.h"
#include "BsMonoManager.h"
#include "BsMonoMethod.h"
#include "BsMonoUtil.h"
#include "Importer/BsTextureImportOptions.h"
#include "Text/BsFontImportOptions.h"
#include "Resources/BsScriptCodeImportOptions.h"
#include "Importer/BsMeshImportOptions.h"
#include "Renderer/BsRenderer.h"
#include "Reflection/BsRTTIType.h"

#include "BsScriptAnimationEvent.generated.h"
#include "BsScriptFont.generated.h"

using namespace std::placeholders;

namespace bs
{
	struct CharRange
	{
		UINT32 start, end;
	};

	ScriptCharRange::ScriptCharRange(MonoObject* instance)
		:ScriptObject(instance)
	{ }

	void ScriptCharRange::initRuntimeData()
	{ }

	ScriptImportOptionsBase::ScriptImportOptionsBase(MonoObject* instance)
		:ScriptObjectBase(instance)
	{ }

	void ScriptImportOptions::initRuntimeData()
	{ }

	MonoObject* ScriptImportOptions::create(const SPtr<ImportOptions>& importOptions)
	{
		UINT32 typeId = importOptions->getRTTI()->getRTTIId();
		switch (typeId)
		{
		case TID_TextureImportOptions:
			return ScriptTextureImportOptions::create(std::static_pointer_cast<TextureImportOptions>(importOptions));
		case TID_MeshImportOptions:
			return ScriptMeshImportOptions::create(std::static_pointer_cast<MeshImportOptions>(importOptions));
		case TID_FontImportOptions:
			return ScriptFontImportOptions::create(std::static_pointer_cast<FontImportOptions>(importOptions));
		case TID_ScriptCodeImportOptions:
			return ScriptScriptCodeImportOptions::create(std::static_pointer_cast<ScriptCodeImportOptions>(importOptions));
		case TID_AudioClipImportOptions:
			return ScriptAudioClipImportOptions::create(std::static_pointer_cast<AudioClipImportOptions>(importOptions));
		}

		MonoObject* managedInstance = metaData.scriptClass->createInstance();
		ScriptImportOptions* scriptObj = ScriptImportOptions::toNative(managedInstance);
		scriptObj->mImportOptions = importOptions;

		return managedInstance;
	}

	ScriptImportOptions::ScriptImportOptions(MonoObject* instance)
		:ScriptObject(instance)
	{
		mImportOptions = bs_shared_ptr_new<ImportOptions>();
	}

	ScriptTextureImportOptions::ScriptTextureImportOptions(MonoObject* instance)
		: ScriptObject(instance)
	{
		mImportOptions = bs_shared_ptr_new<TextureImportOptions>();
	}

	void ScriptTextureImportOptions::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", (void*)&ScriptTextureImportOptions::internal_CreateInstance);
		metaData.scriptClass->addInternalCall("Internal_GetPixelFormat", (void*)&ScriptTextureImportOptions::internal_GetPixelFormat);
		metaData.scriptClass->addInternalCall("Internal_SetPixelFormat", (void*)&ScriptTextureImportOptions::internal_SetPixelFormat);
		metaData.scriptClass->addInternalCall("Internal_GetGenerateMipmaps", (void*)&ScriptTextureImportOptions::internal_GetGenerateMipmaps);
		metaData.scriptClass->addInternalCall("Internal_SetGenerateMipmaps", (void*)&ScriptTextureImportOptions::internal_SetGenerateMipmaps);
		metaData.scriptClass->addInternalCall("Internal_GetMaxMipmapLevel", (void*)&ScriptTextureImportOptions::internal_GetMaxMipmapLevel);
		metaData.scriptClass->addInternalCall("Internal_SetMaxMipmapLevel", (void*)&ScriptTextureImportOptions::internal_SetMaxMipmapLevel);
		metaData.scriptClass->addInternalCall("Internal_GetCPUCached", (void*)&ScriptTextureImportOptions::internal_GetCPUCached);
		metaData.scriptClass->addInternalCall("Internal_SetCPUCached", (void*)&ScriptTextureImportOptions::internal_SetCPUCached);
		metaData.scriptClass->addInternalCall("Internal_GetIsSRGB", (void*)&ScriptTextureImportOptions::internal_GetIsSRGB);
		metaData.scriptClass->addInternalCall("Internal_SetIsSRGB", (void*)&ScriptTextureImportOptions::internal_SetIsSRGB);
		metaData.scriptClass->addInternalCall("Internal_GetIsCubemap", (void*)&ScriptTextureImportOptions::internal_GetIsCubemap);
		metaData.scriptClass->addInternalCall("Internal_SetIsCubemap", (void*)&ScriptTextureImportOptions::internal_SetIsCubemap);
		metaData.scriptClass->addInternalCall("Internal_GetCubemapSourceType", (void*)&ScriptTextureImportOptions::internal_GetCubemapSourceType);
		metaData.scriptClass->addInternalCall("Internal_SetCubemapSourceType", (void*)&ScriptTextureImportOptions::internal_SetCubemapSourceType);
	}

	SPtr<TextureImportOptions> ScriptTextureImportOptions::getTexImportOptions()
	{
		return std::static_pointer_cast<TextureImportOptions>(mImportOptions);
	}

	MonoObject* ScriptTextureImportOptions::create()
	{
		return metaData.scriptClass->createInstance();
	}

	MonoObject* ScriptTextureImportOptions::create(const SPtr<TextureImportOptions>& options)
	{
		MonoObject* managedInstance = metaData.scriptClass->createInstance();
		ScriptTextureImportOptions* scriptObj = ScriptTextureImportOptions::toNative(managedInstance);
		scriptObj->mImportOptions = options;

		return managedInstance;
	}

	void ScriptTextureImportOptions::internal_CreateInstance(MonoObject* instance)
	{
		new (bs_alloc<ScriptTextureImportOptions>()) ScriptTextureImportOptions(instance);
	}

	PixelFormat ScriptTextureImportOptions::internal_GetPixelFormat(ScriptTextureImportOptions* thisPtr)
	{
		return thisPtr->getTexImportOptions()->getFormat();
	}

	void ScriptTextureImportOptions::internal_SetPixelFormat(ScriptTextureImportOptions* thisPtr, PixelFormat value)
	{
		thisPtr->getTexImportOptions()->setFormat(value);
	}

	bool ScriptTextureImportOptions::internal_GetGenerateMipmaps(ScriptTextureImportOptions* thisPtr)
	{
		return thisPtr->getTexImportOptions()->getGenerateMipmaps();
	}

	void ScriptTextureImportOptions::internal_SetGenerateMipmaps(ScriptTextureImportOptions* thisPtr, bool value)
	{
		thisPtr->getTexImportOptions()->setGenerateMipmaps(value);
	}

	UINT32 ScriptTextureImportOptions::internal_GetMaxMipmapLevel(ScriptTextureImportOptions* thisPtr)
	{
		return thisPtr->getTexImportOptions()->getMaxMip();
	}

	void ScriptTextureImportOptions::internal_SetMaxMipmapLevel(ScriptTextureImportOptions* thisPtr, UINT32 value)
	{
		thisPtr->getTexImportOptions()->setMaxMip(value);
	}

	bool ScriptTextureImportOptions::internal_GetCPUCached(ScriptTextureImportOptions* thisPtr)
	{
		return thisPtr->getTexImportOptions()->getCPUCached();
	}

	void ScriptTextureImportOptions::internal_SetCPUCached(ScriptTextureImportOptions* thisPtr, bool value)
	{
		thisPtr->getTexImportOptions()->setCPUCached(value);
	}

	bool ScriptTextureImportOptions::internal_GetIsSRGB(ScriptTextureImportOptions* thisPtr)
	{
		return thisPtr->getTexImportOptions()->getSRGB();
	}

	void ScriptTextureImportOptions::internal_SetIsSRGB(ScriptTextureImportOptions* thisPtr, bool value)
	{
		thisPtr->getTexImportOptions()->setSRGB(value);
	}


	bool ScriptTextureImportOptions::internal_GetIsCubemap(ScriptTextureImportOptions* thisPtr)
	{
		return thisPtr->getTexImportOptions()->getIsCubemap();
	}

	void ScriptTextureImportOptions::internal_SetIsCubemap(ScriptTextureImportOptions* thisPtr, bool value)
	{
		thisPtr->getTexImportOptions()->setIsCubemap(value);
	}

	CubemapSourceType ScriptTextureImportOptions::internal_GetCubemapSourceType(ScriptTextureImportOptions* thisPtr)
	{
		return thisPtr->getTexImportOptions()->getCubemapSourceType();
	}

	void ScriptTextureImportOptions::internal_SetCubemapSourceType(ScriptTextureImportOptions* thisPtr, CubemapSourceType value)
	{
		thisPtr->getTexImportOptions()->setCubemapSourceType(value);
	}

	ScriptMeshImportOptions::ScriptMeshImportOptions(MonoObject* instance)
		:ScriptObject(instance)
	{
		mImportOptions = bs_shared_ptr_new<MeshImportOptions>();
	}

	void ScriptMeshImportOptions::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", (void*)&ScriptMeshImportOptions::internal_CreateInstance);
		metaData.scriptClass->addInternalCall("Internal_GetCPUCached", (void*)&ScriptMeshImportOptions::internal_GetCPUCached);
		metaData.scriptClass->addInternalCall("Internal_SetCPUCached", (void*)&ScriptMeshImportOptions::internal_SetCPUCached);
		metaData.scriptClass->addInternalCall("Internal_GetImportNormals", (void*)&ScriptMeshImportOptions::internal_GetImportNormals);
		metaData.scriptClass->addInternalCall("Internal_SetImportNormals", (void*)&ScriptMeshImportOptions::internal_SetImportNormals);
		metaData.scriptClass->addInternalCall("Internal_GetImportTangents", (void*)&ScriptMeshImportOptions::internal_GetImportTangents);
		metaData.scriptClass->addInternalCall("Internal_SetImportTangents", (void*)&ScriptMeshImportOptions::internal_SetImportTangents);
		metaData.scriptClass->addInternalCall("Internal_GetImportSkin", (void*)&ScriptMeshImportOptions::internal_GetImportSkin);
		metaData.scriptClass->addInternalCall("Internal_SetImportSkin", (void*)&ScriptMeshImportOptions::internal_SetImportSkin);
		metaData.scriptClass->addInternalCall("Internal_GetImportAnimation", (void*)&ScriptMeshImportOptions::internal_GetImportAnimation);
		metaData.scriptClass->addInternalCall("Internal_SetImportAnimation", (void*)&ScriptMeshImportOptions::internal_SetImportAnimation);
		metaData.scriptClass->addInternalCall("Internal_GetImportBlendShapes", (void*)&ScriptMeshImportOptions::internal_GetImportBlendShapes);
		metaData.scriptClass->addInternalCall("Internal_SetImportBlendShapes", (void*)&ScriptMeshImportOptions::internal_SetImportBlendShapes);
		metaData.scriptClass->addInternalCall("Internal_GetKeyFrameReduction", (void*)&ScriptMeshImportOptions::internal_GetKeyFrameReduction);
		metaData.scriptClass->addInternalCall("Internal_SetKeyFrameReduction", (void*)&ScriptMeshImportOptions::internal_SetKeyFrameReduction);
		metaData.scriptClass->addInternalCall("Internal_GetRootMotion", (void*)&ScriptMeshImportOptions::internal_GetRootMotion);
		metaData.scriptClass->addInternalCall("Internal_SetRootMotion", (void*)&ScriptMeshImportOptions::internal_SetRootMotion);
		metaData.scriptClass->addInternalCall("Internal_GetScale", (void*)&ScriptMeshImportOptions::internal_GetScale);
		metaData.scriptClass->addInternalCall("Internal_SetScale", (void*)&ScriptMeshImportOptions::internal_SetScale);
		metaData.scriptClass->addInternalCall("Internal_GetCollisionMeshType", (void*)&ScriptMeshImportOptions::internal_GetCollisionMeshType);
		metaData.scriptClass->addInternalCall("Internal_SetCollisionMeshType", (void*)&ScriptMeshImportOptions::internal_SetCollisionMeshType);
		metaData.scriptClass->addInternalCall("Internal_GetAnimationClipSplits", (void*)&ScriptMeshImportOptions::internal_GetAnimationClipSplits);
		metaData.scriptClass->addInternalCall("Internal_SetAnimationClipSplits", (void*)&ScriptMeshImportOptions::internal_SetAnimationClipSplits);
		metaData.scriptClass->addInternalCall("Internal_GetAnimationEvents", (void*)&ScriptMeshImportOptions::internal_GetAnimationEvents);
		metaData.scriptClass->addInternalCall("Internal_SetAnimationEvents", (void*)&ScriptMeshImportOptions::internal_SetAnimationEvents);
	}

	SPtr<MeshImportOptions> ScriptMeshImportOptions::getMeshImportOptions()
	{
		return std::static_pointer_cast<MeshImportOptions>(mImportOptions);
	}

	MonoObject* ScriptMeshImportOptions::create()
	{
		return metaData.scriptClass->createInstance();
	}

	MonoObject* ScriptMeshImportOptions::create(const SPtr<MeshImportOptions>& options)
	{
		MonoObject* managedInstance = metaData.scriptClass->createInstance();
		ScriptMeshImportOptions* scriptObj = ScriptMeshImportOptions::toNative(managedInstance);
		scriptObj->mImportOptions = options;

		return managedInstance;
	}

	void ScriptMeshImportOptions::internal_CreateInstance(MonoObject* instance)
	{
		new (bs_alloc<ScriptMeshImportOptions>()) ScriptMeshImportOptions(instance);
	}

	bool ScriptMeshImportOptions::internal_GetCPUCached(ScriptMeshImportOptions* thisPtr)
	{
		return thisPtr->getMeshImportOptions()->getCPUCached();
	}

	void ScriptMeshImportOptions::internal_SetCPUCached(ScriptMeshImportOptions* thisPtr, bool value)
	{
		thisPtr->getMeshImportOptions()->setCPUCached(value);
	}

	bool ScriptMeshImportOptions::internal_GetImportNormals(ScriptMeshImportOptions* thisPtr)
	{
		return thisPtr->getMeshImportOptions()->getImportNormals();
	}

	void ScriptMeshImportOptions::internal_SetImportNormals(ScriptMeshImportOptions* thisPtr, bool value)
	{
		thisPtr->getMeshImportOptions()->setImportNormals(value);
	}

	bool ScriptMeshImportOptions::internal_GetImportTangents(ScriptMeshImportOptions* thisPtr)
	{
		return thisPtr->getMeshImportOptions()->getImportTangents();
	}

	void ScriptMeshImportOptions::internal_SetImportTangents(ScriptMeshImportOptions* thisPtr, bool value)
	{
		thisPtr->getMeshImportOptions()->setImportTangents(value);
	}

	bool ScriptMeshImportOptions::internal_GetImportSkin(ScriptMeshImportOptions* thisPtr)
	{
		return thisPtr->getMeshImportOptions()->getImportSkin();
	}

	void ScriptMeshImportOptions::internal_SetImportSkin(ScriptMeshImportOptions* thisPtr, bool value)
	{
		thisPtr->getMeshImportOptions()->setImportSkin(value);
	}

	bool ScriptMeshImportOptions::internal_GetImportAnimation(ScriptMeshImportOptions* thisPtr)
	{
		return thisPtr->getMeshImportOptions()->getImportAnimation();
	}

	void ScriptMeshImportOptions::internal_SetImportAnimation(ScriptMeshImportOptions* thisPtr, bool value)
	{
		thisPtr->getMeshImportOptions()->setImportAnimation(value);
	}

	bool ScriptMeshImportOptions::internal_GetImportBlendShapes(ScriptMeshImportOptions* thisPtr)
	{
		return thisPtr->getMeshImportOptions()->getImportBlendShapes();
	}

	void ScriptMeshImportOptions::internal_SetImportBlendShapes(ScriptMeshImportOptions* thisPtr, bool value)
	{
		thisPtr->getMeshImportOptions()->setImportBlendShapes(value);
	}

	bool ScriptMeshImportOptions::internal_GetKeyFrameReduction(ScriptMeshImportOptions* thisPtr)
	{
		return thisPtr->getMeshImportOptions()->getKeyFrameReduction();
	}

	void ScriptMeshImportOptions::internal_SetKeyFrameReduction(ScriptMeshImportOptions* thisPtr, bool value)
	{
		thisPtr->getMeshImportOptions()->setKeyFrameReduction(value);
	}

	bool ScriptMeshImportOptions::internal_GetRootMotion(ScriptMeshImportOptions* thisPtr)
	{
		return thisPtr->getMeshImportOptions()->getImportRootMotion();
	}

	void ScriptMeshImportOptions::internal_SetRootMotion(ScriptMeshImportOptions* thisPtr, bool value)
	{
		thisPtr->getMeshImportOptions()->setImportRootMotion(value);
	}

	float ScriptMeshImportOptions::internal_GetScale(ScriptMeshImportOptions* thisPtr)
	{
		return thisPtr->getMeshImportOptions()->getImportScale();
	}

	void ScriptMeshImportOptions::internal_SetScale(ScriptMeshImportOptions* thisPtr, float value)
	{
		thisPtr->getMeshImportOptions()->setImportScale(value);
	}

	int ScriptMeshImportOptions::internal_GetCollisionMeshType(ScriptMeshImportOptions* thisPtr)
	{
		return (int)thisPtr->getMeshImportOptions()->getCollisionMeshType();
	}

	void ScriptMeshImportOptions::internal_SetCollisionMeshType(ScriptMeshImportOptions* thisPtr, int value)
	{
		thisPtr->getMeshImportOptions()->setCollisionMeshType((CollisionMeshType)value);
	}

	MonoArray* ScriptMeshImportOptions::internal_GetAnimationClipSplits(ScriptMeshImportOptions* thisPtr)
	{
		SPtr<MeshImportOptions> io = thisPtr->getMeshImportOptions();

		Vector<AnimationSplitInfo> splitInfos = io->getAnimationClipSplits();
		UINT32 numSplitInfos = (UINT32)splitInfos.size();
		ScriptArray outputArray = ScriptArray::create<ScriptAnimationSplitInfo>(numSplitInfos);
		for(UINT32 i = 0; i < numSplitInfos; i++)
			outputArray.set(i, ScriptAnimationSplitInfo::toManaged(splitInfos[i]));

		return outputArray.getInternal();
	}

	void ScriptMeshImportOptions::internal_SetAnimationClipSplits(ScriptMeshImportOptions* thisPtr, MonoArray* value)
	{
		SPtr<MeshImportOptions> io = thisPtr->getMeshImportOptions();

		if(value == nullptr)
		{
			io->setAnimationClipSplits({});
			return;
		}

		ScriptArray inputArray(value);

		UINT32 numSplits = inputArray.size();
		Vector<AnimationSplitInfo> splitInfos(numSplits);
		for (UINT32 i = 0; i < numSplits; i++)
		{
			MonoObject* monoSplitInfo = inputArray.get<MonoObject*>(i);

			if(monoSplitInfo != nullptr)
				splitInfos[i] = ScriptAnimationSplitInfo::fromManaged(monoSplitInfo);
		}

		io->setAnimationClipSplits(splitInfos);
	}

	MonoArray* ScriptMeshImportOptions::internal_GetAnimationEvents(ScriptMeshImportOptions* thisPtr)
	{
		SPtr<MeshImportOptions> io = thisPtr->getMeshImportOptions();

		Vector<ImportedAnimationEvents> animationEvents = io->getAnimationEvents();
		UINT32 count = (UINT32)animationEvents.size();
		ScriptArray outputArray = ScriptArray::create<ScriptImportedAnimationEvents>(count);
		for (UINT32 i = 0; i < count; i++)
			outputArray.set(i, ScriptImportedAnimationEvents::toManaged(animationEvents[i]));

		return outputArray.getInternal();
	}

	void ScriptMeshImportOptions::internal_SetAnimationEvents(ScriptMeshImportOptions* thisPtr, MonoArray* value)
	{
		ScriptArray inputArray(value);

		SPtr<MeshImportOptions> io = thisPtr->getMeshImportOptions();

		UINT32 count = inputArray.size();
		Vector<ImportedAnimationEvents> animationEvents(count);
		for (UINT32 i = 0; i < count; i++)
			animationEvents[i] = ScriptImportedAnimationEvents::fromManaged(inputArray.get<MonoObject*>(i));

		io->setAnimationEvents(animationEvents);
	}

	ScriptFontImportOptions::ScriptFontImportOptions(MonoObject* instance)
		:ScriptObject(instance)
	{
		mImportOptions = bs_shared_ptr_new<FontImportOptions>();
	}

	void ScriptFontImportOptions::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", (void*)&ScriptFontImportOptions::internal_CreateInstance);
		metaData.scriptClass->addInternalCall("Internal_GetFontSizes", (void*)&ScriptFontImportOptions::internal_GetFontSizes);
		metaData.scriptClass->addInternalCall("Internal_SetFontSizes", (void*)&ScriptFontImportOptions::internal_SetFontSizes);
		metaData.scriptClass->addInternalCall("Internal_GetDPI", (void*)&ScriptFontImportOptions::internal_GetDPI);
		metaData.scriptClass->addInternalCall("Internal_SetDPI", (void*)&ScriptFontImportOptions::internal_SetDPI);
		metaData.scriptClass->addInternalCall("Internal_GetRenderMode", (void*)&ScriptFontImportOptions::internal_GetRenderMode);
		metaData.scriptClass->addInternalCall("Internal_SetRenderMode", (void*)&ScriptFontImportOptions::internal_SetRenderMode);
		metaData.scriptClass->addInternalCall("Internal_GetBold", (void*)&ScriptFontImportOptions::internal_GetBold);
		metaData.scriptClass->addInternalCall("Internal_SetBold", (void*)&ScriptFontImportOptions::internal_SetBold);
		metaData.scriptClass->addInternalCall("Internal_GetItalic", (void*)&ScriptFontImportOptions::internal_GetItalic);
		metaData.scriptClass->addInternalCall("Internal_SetItalic", (void*)&ScriptFontImportOptions::internal_SetItalic);
		metaData.scriptClass->addInternalCall("Internal_GetCharRanges", (void*)&ScriptFontImportOptions::internal_GetCharRanges);
		metaData.scriptClass->addInternalCall("Internal_SetCharRanges", (void*)&ScriptFontImportOptions::internal_SetCharRanges);
	}

	SPtr<FontImportOptions> ScriptFontImportOptions::getFontImportOptions()
	{
		return std::static_pointer_cast<FontImportOptions>(mImportOptions);
	}

	MonoObject* ScriptFontImportOptions::create()
	{
		return metaData.scriptClass->createInstance();
	}

	MonoObject* ScriptFontImportOptions::create(const SPtr<FontImportOptions>& options)
	{
		MonoObject* managedInstance = metaData.scriptClass->createInstance();
		ScriptFontImportOptions* scriptObj = ScriptFontImportOptions::toNative(managedInstance);
		scriptObj->mImportOptions = options;

		return managedInstance;
	}

	void ScriptFontImportOptions::internal_CreateInstance(MonoObject* instance)
	{
		new (bs_alloc<ScriptFontImportOptions>()) ScriptFontImportOptions(instance);
	}

	MonoArray* ScriptFontImportOptions::internal_GetFontSizes(ScriptFontImportOptions* thisPtr)
	{
		Vector<UINT32> fontSizes = thisPtr->getFontImportOptions()->getFontSizes();

		ScriptArray outArray = ScriptArray::create<UINT32>((UINT32)fontSizes.size());
		for (UINT32 i = 0; i < fontSizes.size(); i++)
			outArray.set(i, fontSizes[i]);

		return outArray.getInternal();
	}

	void ScriptFontImportOptions::internal_SetFontSizes(ScriptFontImportOptions* thisPtr, MonoArray* value)
	{
		ScriptArray inArray(value);

		Vector<UINT32> fontSizes(inArray.size());
		for (UINT32 i = 0; i < inArray.size(); i++)
			fontSizes[i] = inArray.get<UINT32>(i);

		thisPtr->getFontImportOptions()->setFontSizes(fontSizes);
	}

	UINT32 ScriptFontImportOptions::internal_GetDPI(ScriptFontImportOptions* thisPtr)
	{
		return thisPtr->getFontImportOptions()->getDPI();
	}

	void ScriptFontImportOptions::internal_SetDPI(ScriptFontImportOptions* thisPtr, UINT32 value)
	{
		thisPtr->getFontImportOptions()->setDPI(value);
	}

	FontRenderMode ScriptFontImportOptions::internal_GetRenderMode(ScriptFontImportOptions* thisPtr)
	{
		return thisPtr->getFontImportOptions()->getRenderMode();
	}

	void ScriptFontImportOptions::internal_SetRenderMode(ScriptFontImportOptions* thisPtr, FontRenderMode value)
	{
		thisPtr->getFontImportOptions()->setRenderMode(value);
	}

	bool ScriptFontImportOptions::internal_GetBold(ScriptFontImportOptions* thisPtr)
	{
		return thisPtr->getFontImportOptions()->getBold();
	}

	void ScriptFontImportOptions::internal_SetBold(ScriptFontImportOptions* thisPtr, bool value)
	{
		thisPtr->getFontImportOptions()->setBold(value);
	}

	bool ScriptFontImportOptions::internal_GetItalic(ScriptFontImportOptions* thisPtr)
	{
		return thisPtr->getFontImportOptions()->getItalic();
	}

	void ScriptFontImportOptions::internal_SetItalic(ScriptFontImportOptions* thisPtr, bool value)
	{
		thisPtr->getFontImportOptions()->setItalic(value);
	}

	MonoArray* ScriptFontImportOptions::internal_GetCharRanges(ScriptFontImportOptions* thisPtr)
	{
		Vector<std::pair<UINT32, UINT32>> charRanges = thisPtr->getFontImportOptions()->getCharIndexRanges();

		ScriptArray outArray = ScriptArray::create<ScriptCharRange>((UINT32)charRanges.size());
		for (UINT32 i = 0; i < (UINT32)charRanges.size(); i++)
		{
			CharRange range;
			range.start = charRanges[i].first;
			range.end = charRanges[i].second;
			outArray.set(i, range);
		}

		return outArray.getInternal();
	}

	void ScriptFontImportOptions::internal_SetCharRanges(ScriptFontImportOptions* thisPtr, MonoArray* value)
	{
		ScriptArray inArray(value);

		thisPtr->getFontImportOptions()->clearCharIndexRanges();
		for (UINT32 i = 0; i < inArray.size(); i++)
		{
			CharRange range = inArray.get<CharRange>(i);
			thisPtr->getFontImportOptions()->addCharIndexRange(range.start, range.end);
		}
	}

	ScriptScriptCodeImportOptions::ScriptScriptCodeImportOptions(MonoObject* instance)
		:ScriptObject(instance)
	{
		mImportOptions = bs_shared_ptr_new<ScriptCodeImportOptions>();
	}

	void ScriptScriptCodeImportOptions::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", (void*)&ScriptScriptCodeImportOptions::internal_CreateInstance);
		metaData.scriptClass->addInternalCall("Internal_IsEditorScript", (void*)&ScriptScriptCodeImportOptions::internal_IsEditorScript);
		metaData.scriptClass->addInternalCall("Internal_SetEditorScript", (void*)&ScriptScriptCodeImportOptions::internal_SetEditorScript);
	}

	SPtr<ScriptCodeImportOptions> ScriptScriptCodeImportOptions::getCodeImportOptions()
	{
		return std::static_pointer_cast<ScriptCodeImportOptions>(mImportOptions);
	}

	MonoObject* ScriptScriptCodeImportOptions::create()
	{
		return metaData.scriptClass->createInstance();
	}

	MonoObject* ScriptScriptCodeImportOptions::create(const SPtr<ScriptCodeImportOptions>& options)
	{
		MonoObject* managedInstance = metaData.scriptClass->createInstance();
		ScriptScriptCodeImportOptions* scriptObj = ScriptScriptCodeImportOptions::toNative(managedInstance);
		scriptObj->mImportOptions = options;

		return managedInstance;
	}

	void ScriptScriptCodeImportOptions::internal_CreateInstance(MonoObject* instance)
	{
		new (bs_alloc<ScriptScriptCodeImportOptions>()) ScriptScriptCodeImportOptions(instance);
	}

	bool ScriptScriptCodeImportOptions::internal_IsEditorScript(ScriptScriptCodeImportOptions* thisPtr)
	{
		return thisPtr->getCodeImportOptions()->isEditorScript();
	}

	void ScriptScriptCodeImportOptions::internal_SetEditorScript(ScriptScriptCodeImportOptions* thisPtr, bool value)
	{
		thisPtr->getCodeImportOptions()->setEditorScript(value);
	}

	ScriptAudioClipImportOptions::ScriptAudioClipImportOptions(MonoObject* instance)
		:ScriptObject(instance)
	{
		mImportOptions = bs_shared_ptr_new<AudioClipImportOptions>();
	}

	void ScriptAudioClipImportOptions::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", (void*)&ScriptAudioClipImportOptions::internal_CreateInstance);
		metaData.scriptClass->addInternalCall("Internal_GetFormat", (void*)&ScriptAudioClipImportOptions::internal_GetFormat);
		metaData.scriptClass->addInternalCall("Internal_SetFormat", (void*)&ScriptAudioClipImportOptions::internal_SetFormat);
		metaData.scriptClass->addInternalCall("Internal_GetReadMode", (void*)&ScriptAudioClipImportOptions::internal_GetReadMode);
		metaData.scriptClass->addInternalCall("Internal_SetReadMode", (void*)&ScriptAudioClipImportOptions::internal_SetReadMode);
		metaData.scriptClass->addInternalCall("Internal_GetIs3D", (void*)&ScriptAudioClipImportOptions::internal_GetIs3D);
		metaData.scriptClass->addInternalCall("Internal_SetIs3D", (void*)&ScriptAudioClipImportOptions::internal_SetIs3D);
		metaData.scriptClass->addInternalCall("Internal_GetBitDepth", (void*)&ScriptAudioClipImportOptions::internal_GetBitDepth);
		metaData.scriptClass->addInternalCall("Internal_SetBitDepth", (void*)&ScriptAudioClipImportOptions::internal_SetBitDepth);
	}

	SPtr<AudioClipImportOptions> ScriptAudioClipImportOptions::getClipImportOptions()
	{
		return std::static_pointer_cast<AudioClipImportOptions>(mImportOptions);
	}

	MonoObject* ScriptAudioClipImportOptions::create()
	{
		return metaData.scriptClass->createInstance();
	}

	MonoObject* ScriptAudioClipImportOptions::create(const SPtr<AudioClipImportOptions>& options)
	{
		MonoObject* managedInstance = metaData.scriptClass->createInstance();
		ScriptAudioClipImportOptions* scriptObj = ScriptAudioClipImportOptions::toNative(managedInstance);
		scriptObj->mImportOptions = options;

		return managedInstance;
	}

	void ScriptAudioClipImportOptions::internal_CreateInstance(MonoObject* instance)
	{
		new (bs_alloc<ScriptAudioClipImportOptions>()) ScriptAudioClipImportOptions(instance);
	}

	AudioFormat ScriptAudioClipImportOptions::internal_GetFormat(ScriptAudioClipImportOptions* thisPtr)
	{
		auto io = thisPtr->getClipImportOptions();
		return io->getFormat();
	}

	void ScriptAudioClipImportOptions::internal_SetFormat(ScriptAudioClipImportOptions* thisPtr, AudioFormat format)
	{
		auto io = thisPtr->getClipImportOptions();
		io->setFormat(format);
	}

	AudioReadMode ScriptAudioClipImportOptions::internal_GetReadMode(ScriptAudioClipImportOptions* thisPtr)
	{
		auto io = thisPtr->getClipImportOptions();
		return io->getReadMode();
	}

	void ScriptAudioClipImportOptions::internal_SetReadMode(ScriptAudioClipImportOptions* thisPtr, AudioReadMode readMode)
	{
		auto io = thisPtr->getClipImportOptions();
		io->setReadMode(readMode);
	}

	bool ScriptAudioClipImportOptions::internal_GetIs3D(ScriptAudioClipImportOptions* thisPtr)
	{
		auto io = thisPtr->getClipImportOptions();
		return io->getIs3D();
	}

	void ScriptAudioClipImportOptions::internal_SetIs3D(ScriptAudioClipImportOptions* thisPtr, bool is3d)
	{
		auto io = thisPtr->getClipImportOptions();
		io->setIs3D(is3d);
	}

	UINT32 ScriptAudioClipImportOptions::internal_GetBitDepth(ScriptAudioClipImportOptions* thisPtr)
	{
		auto io = thisPtr->getClipImportOptions();
		return io->getBitDepth();
	}

	void ScriptAudioClipImportOptions::internal_SetBitDepth(ScriptAudioClipImportOptions* thisPtr, UINT32 bitDepth)
	{
		auto io = thisPtr->getClipImportOptions();
		io->setBitDepth(bitDepth);
	}

	MonoField* ScriptAnimationSplitInfo::nameField = nullptr;
	MonoField* ScriptAnimationSplitInfo::startFrameField = nullptr;
	MonoField* ScriptAnimationSplitInfo::endFrameField = nullptr;
	MonoField* ScriptAnimationSplitInfo::isAdditiveField = nullptr;

	ScriptAnimationSplitInfo::ScriptAnimationSplitInfo(MonoObject* instance)
		:ScriptObject(instance)
	{ }

	void ScriptAnimationSplitInfo::initRuntimeData()
	{
		nameField = metaData.scriptClass->getField("name");
		startFrameField = metaData.scriptClass->getField("startFrame");
		endFrameField = metaData.scriptClass->getField("endFrame");
		isAdditiveField = metaData.scriptClass->getField("isAdditive");
	}

	AnimationSplitInfo ScriptAnimationSplitInfo::fromManaged(MonoObject* instance)
	{
		AnimationSplitInfo output;

		MonoString* monoName = nullptr;
		nameField->get(instance, &monoName);

		output.name = MonoUtil::monoToString(monoName);

		startFrameField->get(instance, &output.startFrame);
		endFrameField->get(instance, &output.endFrame);
		isAdditiveField->get(instance, &output.isAdditive);

		return output;
	}

	MonoObject* ScriptAnimationSplitInfo::toManaged(const AnimationSplitInfo& splitInfo)
	{
		MonoString* monoString = MonoUtil::stringToMono(splitInfo.name);
		UINT32 startFrame = splitInfo.startFrame;
		UINT32 endFrame = splitInfo.endFrame;
		bool isAdditive = splitInfo.isAdditive;

		void* params[4] = { monoString, &startFrame, &endFrame, &isAdditive };
		return metaData.scriptClass->createInstance("string,int,int,bool", params);
	}

	MonoField* ScriptImportedAnimationEvents::nameField = nullptr;
	MonoField* ScriptImportedAnimationEvents::eventsField = nullptr;

	ScriptImportedAnimationEvents::ScriptImportedAnimationEvents(MonoObject* instance)
		:ScriptObject(instance)
	{ }

	void ScriptImportedAnimationEvents::initRuntimeData()
	{
		nameField = metaData.scriptClass->getField("name");
		eventsField = metaData.scriptClass->getField("events");
	}

	ImportedAnimationEvents ScriptImportedAnimationEvents::fromManaged(MonoObject* instance)
	{
		ImportedAnimationEvents output;

		MonoString* monoName = nullptr;
		nameField->get(instance, &monoName);

		output.name = MonoUtil::monoToString(monoName);

		MonoArray* monoEvents;
		eventsField->get(instance, &monoEvents);

		if (monoEvents != nullptr)
		{
			ScriptArray scriptEvents(monoEvents);
			for (UINT32 i = 0; i < scriptEvents.size(); i++)
			{
				AnimationEvent event = ScriptAnimationEvent::fromInterop(scriptEvents.get<__AnimationEventInterop>(i));
				output.events.push_back(event);
			}
		}

		return output;
	}

	MonoObject* ScriptImportedAnimationEvents::toManaged(const ImportedAnimationEvents& events)
	{
		MonoString* monoString = MonoUtil::stringToMono(events.name);
		
		UINT32 numEvents = (UINT32)events.events.size();
		ScriptArray scriptEvents = ScriptArray::create<ScriptAnimationEvent>(numEvents);

		for (UINT32 i = 0; i < numEvents; i++)
			scriptEvents.set(i, ScriptAnimationEvent::toInterop(events.events[i]));

		MonoObject* instance = metaData.scriptClass->createInstance();
		nameField->set(instance, monoString);
		eventsField->set(instance, scriptEvents.getInternal());

		return instance;
	}
}