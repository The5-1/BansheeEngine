//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Wrappers/GUI/BsScriptGUIColorField.h"
#include "BsScriptMeta.h"
#include "BsMonoClass.h"
#include "BsMonoManager.h"
#include "BsMonoMethod.h"
#include "BsMonoUtil.h"
#include "GUI/BsGUIColorField.h"
#include "GUI/BsGUIOptions.h"
#include "GUI/BsGUIContent.h"
#include "Wrappers/GUI/BsScriptGUIContent.h"

using namespace std::placeholders;

namespace bs
{
	ScriptGUIColorField::OnClickedThunkDef ScriptGUIColorField::onClickedThunk;

	ScriptGUIColorField::ScriptGUIColorField(MonoObject* instance, GUIColorField* colorField)
		:TScriptGUIElement(instance, colorField)
	{

	}

	void ScriptGUIColorField::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", (void*)&ScriptGUIColorField::internal_createInstance);
		metaData.scriptClass->addInternalCall("Internal_GetValue", (void*)&ScriptGUIColorField::internal_getValue);
		metaData.scriptClass->addInternalCall("Internal_SetValue", (void*)&ScriptGUIColorField::internal_setValue);
		metaData.scriptClass->addInternalCall("Internal_SetTint", (void*)&ScriptGUIColorField::internal_setTint);

		onClickedThunk = (OnClickedThunkDef)metaData.scriptClass->getMethod("Internal_DoOnClicked")->getThunk();
	}

	void ScriptGUIColorField::internal_createInstance(MonoObject* instance, MonoObject* title, UINT32 titleWidth,
		MonoString* style, MonoArray* guiOptions, bool withTitle)
	{
		GUIOptions options;

		ScriptArray scriptArray(guiOptions);
		UINT32 arrayLen = scriptArray.size();
		for (UINT32 i = 0; i < arrayLen; i++)
			options.addOption(scriptArray.get<GUIOption>(i));

		String styleName = toString(MonoUtil::monoToWString(style));

		GUIColorField* guiField = nullptr;
		if (withTitle)
		{
			GUIContent nativeContent(ScriptGUIContent::getText(title), ScriptGUIContent::getImage(title), ScriptGUIContent::getTooltip(title));
			guiField = GUIColorField::create(nativeContent, titleWidth, options, styleName);
		}
		else
		{
			guiField = GUIColorField::create(options, styleName);
		}

		ScriptGUIColorField* nativeInstance = new (bs_alloc<ScriptGUIColorField>()) ScriptGUIColorField(instance, guiField);
		guiField->onClicked.connect(std::bind(&ScriptGUIColorField::onClicked, nativeInstance));
	}

	void ScriptGUIColorField::internal_getValue(ScriptGUIColorField* nativeInstance, Color* output)
	{
		GUIColorField* colorField = static_cast<GUIColorField*>(nativeInstance->getGUIElement());
		*output = colorField->getValue();
	}

	void ScriptGUIColorField::internal_setValue(ScriptGUIColorField* nativeInstance, Color* value)
	{
		GUIColorField* colorField = static_cast<GUIColorField*>(nativeInstance->getGUIElement());
		return colorField->setValue(*value);
	}

	void ScriptGUIColorField::internal_setTint(ScriptGUIColorField* nativeInstance, Color* color)
	{
		GUIColorField* colorField = (GUIColorField*)nativeInstance->getGUIElement();
		colorField->setTint(*color);
	}

	void ScriptGUIColorField::onClicked()
	{
		MonoUtil::invokeThunk(onClickedThunk, getManagedInstance());
	}
}