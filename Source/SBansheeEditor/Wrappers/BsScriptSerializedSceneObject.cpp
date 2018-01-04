//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Wrappers/BsScriptSerializedSceneObject.h"
#include "BsScriptMeta.h"
#include "BsMonoClass.h"
#include "Wrappers/BsScriptSceneObject.h"
#include "Scene/BsSceneObject.h"
#include "Serialization/BsMemorySerializer.h"

namespace bs
{
	ScriptSerializedSceneObject::ScriptSerializedSceneObject(MonoObject* instance, const HSceneObject& so, bool recordHierarchy)
		: ScriptObject(instance), mSO(so), mRecordHierarchy(recordHierarchy), mSerializedObject(nullptr), mSerializedObjectSize(0)
	{
		if (mSO.isDestroyed())
			return;

		UINT32 numChildren = mSO->getNumChildren();
		HSceneObject* children = nullptr;

		if (!mRecordHierarchy)
		{
			children = bs_stack_new<HSceneObject>(numChildren);
			for (UINT32 i = 0; i < numChildren; i++)
			{
				HSceneObject child = mSO->getChild(i);
				children[i] = child;

				child->setParent(HSceneObject());
			}
		}

		bool isInstantiated = !mSO->hasFlag(SOF_DontInstantiate);
		mSO->_setFlags(SOF_DontInstantiate);

		MemorySerializer serializer;
		mSerializedObject = serializer.encode(mSO.get(), mSerializedObjectSize);

		if (isInstantiated)
			mSO->_unsetFlags(SOF_DontInstantiate);

		mSceneObjectProxy = EditorUtility::createProxy(mSO);

		if (!mRecordHierarchy)
		{
			for (UINT32 i = 0; i < numChildren; i++)
				children[i]->setParent(mSO->getHandle());

			bs_stack_delete(children, numChildren);
		}
	}

	ScriptSerializedSceneObject::~ScriptSerializedSceneObject()
	{
		if (mSerializedObject != nullptr)
			bs_free(mSerializedObject);
	}

	void ScriptSerializedSceneObject::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", (void*)&ScriptSerializedSceneObject::internal_CreateInstance);
		metaData.scriptClass->addInternalCall("Internal_Restore", (void*)&ScriptSerializedSceneObject::internal_Restore);
	}

	void ScriptSerializedSceneObject::internal_CreateInstance(MonoObject* instance, ScriptSceneObject* so, bool hierarchy)
	{
		HSceneObject sceneObj;
		if (so != nullptr)
			sceneObj = so->getNativeSceneObject();

		new (bs_alloc<ScriptSerializedSceneObject>()) ScriptSerializedSceneObject(instance, sceneObj, hierarchy);
	}

	void ScriptSerializedSceneObject::internal_Restore(ScriptSerializedSceneObject* thisPtr)
	{
		HSceneObject sceneObj = thisPtr->mSO;

		if (sceneObj.isDestroyed())
			return;

		HSceneObject parent = sceneObj->getParent();

		UINT32 numChildren = sceneObj->getNumChildren();
		HSceneObject* children = nullptr;
		if (!thisPtr->mRecordHierarchy)
		{
			children = bs_stack_new<HSceneObject>(numChildren);
			for (UINT32 i = 0; i < numChildren; i++)
			{
				HSceneObject child = sceneObj->getChild(i);
				children[i] = child;

				child->setParent(HSceneObject());
			}
		}

		sceneObj->destroy(true);

		GameObjectManager::instance().setDeserializationMode(GODM_RestoreExternal | GODM_UseNewIds);

		MemorySerializer serializer;
		SPtr<SceneObject> restored = std::static_pointer_cast<SceneObject>(
			serializer.decode(thisPtr->mSerializedObject, thisPtr->mSerializedObjectSize));

		EditorUtility::restoreIds(restored->getHandle(), thisPtr->mSceneObjectProxy);
		restored->setParent(parent);

		if (!thisPtr->mRecordHierarchy)
		{
			for (UINT32 i = 0; i < numChildren; i++)
				children[i]->setParent(restored->getHandle());

			bs_stack_delete(children, numChildren);
		}

		restored->_instantiate();
	}
}