//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Wrappers/GUI/BsScriptGUIVector3Field.h"
#include "BsScriptMeta.h"
#include "BsMonoClass.h"
#include "BsMonoManager.h"
#include "BsMonoMethod.h"
#include "2D/BsSpriteTexture.h"
#include "BsMonoUtil.h"
#include "GUI/BsGUIVector3Field.h"
#include "GUI/BsGUIOptions.h"
#include "GUI/BsGUIContent.h"
#include "Wrappers/GUI/BsScriptGUIContent.h"
#include "Wrappers/BsScriptVector.h"

using namespace std::placeholders;

namespace bs
{
	ScriptGUIVector3Field::OnChangedThunkDef ScriptGUIVector3Field::onChangedThunk;
	ScriptGUIVector3Field::OnConfirmedThunkDef ScriptGUIVector3Field::onConfirmedThunk;

	ScriptGUIVector3Field::ScriptGUIVector3Field(MonoObject* instance, GUIVector3Field* vector3Field)
		:TScriptGUIElement(instance, vector3Field)
	{

	}

	void ScriptGUIVector3Field::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", (void*)&ScriptGUIVector3Field::internal_createInstance);
		metaData.scriptClass->addInternalCall("Internal_GetValue", (void*)&ScriptGUIVector3Field::internal_getValue);
		metaData.scriptClass->addInternalCall("Internal_SetValue", (void*)&ScriptGUIVector3Field::internal_setValue);
		metaData.scriptClass->addInternalCall("Internal_HasInputFocus", (void*)&ScriptGUIVector3Field::internal_hasInputFocus);
		metaData.scriptClass->addInternalCall("Internal_SetTint", (void*)&ScriptGUIVector3Field::internal_setTint);

		onChangedThunk = (OnChangedThunkDef)metaData.scriptClass->getMethod("Internal_DoOnChanged", 1)->getThunk();
		onConfirmedThunk = (OnConfirmedThunkDef)metaData.scriptClass->getMethod("Internal_DoOnConfirmed", 0)->getThunk();
	}

	void ScriptGUIVector3Field::internal_createInstance(MonoObject* instance, MonoObject* title, UINT32 titleWidth,
		MonoString* style, MonoArray* guiOptions, bool withTitle)
	{
		GUIOptions options;

		ScriptArray scriptArray(guiOptions);
		UINT32 arrayLen = scriptArray.size();
		for (UINT32 i = 0; i < arrayLen; i++)
			options.addOption(scriptArray.get<GUIOption>(i));

		String styleName = toString(MonoUtil::monoToWString(style));

		GUIVector3Field* field = nullptr;
		if (withTitle)
		{
			GUIContent nativeContent(ScriptGUIContent::getText(title), ScriptGUIContent::getImage(title), ScriptGUIContent::getTooltip(title));
			field = GUIVector3Field::create(nativeContent, titleWidth, options, styleName);
		}
		else
		{
			field = GUIVector3Field::create(options, styleName);
		}


		auto nativeInstance = new (bs_alloc<ScriptGUIVector3Field>()) ScriptGUIVector3Field(instance, field);
		field->onValueChanged.connect(std::bind(&ScriptGUIVector3Field::onChanged, nativeInstance, _1));
		field->onConfirm.connect(std::bind(&ScriptGUIVector3Field::onConfirmed, nativeInstance));
	}

	void ScriptGUIVector3Field::internal_getValue(ScriptGUIVector3Field* nativeInstance, Vector3* output)
	{
		GUIVector3Field* field = static_cast<GUIVector3Field*>(nativeInstance->getGUIElement());
		*output = field->getValue();
	}

	void ScriptGUIVector3Field::internal_setValue(ScriptGUIVector3Field* nativeInstance, Vector3* value)
	{
		GUIVector3Field* field = static_cast<GUIVector3Field*>(nativeInstance->getGUIElement());
		return field->setValue(*value);
	}

	void ScriptGUIVector3Field::internal_hasInputFocus(ScriptGUIVector3Field* nativeInstance, bool* output)
	{
		GUIVector3Field* field = static_cast<GUIVector3Field*>(nativeInstance->getGUIElement());
		*output = field->hasInputFocus();
	}

	void ScriptGUIVector3Field::internal_setTint(ScriptGUIVector3Field* nativeInstance, Color* color)
	{
		GUIVector3Field* field = (GUIVector3Field*)nativeInstance->getGUIElement();
		field->setTint(*color);
	}

	void ScriptGUIVector3Field::onChanged(const Vector3& newValue)
	{
		MonoUtil::invokeThunk(onChangedThunk, getManagedInstance(), ScriptVector3::box(newValue));
	}

	void ScriptGUIVector3Field::onConfirmed()
	{
		MonoUtil::invokeThunk(onConfirmedThunk, getManagedInstance());
	}
}