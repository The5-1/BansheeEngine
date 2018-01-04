//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Serialization/BsManagedSerializableObject.h"
#include "RTTI/BsManagedSerializableObjectRTTI.h"
#include "Serialization/BsManagedSerializableObjectInfo.h"
#include "Serialization/BsManagedSerializableField.h"
#include "Serialization/BsScriptAssemblyManager.h"
#include "BsMonoField.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"

namespace bs
{
	inline size_t ManagedSerializableObject::Hash::operator()(const ManagedSerializableFieldKey& x) const
	{
		size_t seed = 0;
		hash_combine(seed, (UINT32)x.mFieldId);
		hash_combine(seed, (UINT32)x.mTypeId);

		return seed;
	}

	inline bool ManagedSerializableObject::Equals::operator()(const ManagedSerializableFieldKey& a, const ManagedSerializableFieldKey& b) const
	{
		return a.mFieldId == b.mFieldId && a.mTypeId == b.mTypeId;
	}

	ManagedSerializableObject::ManagedSerializableObject(const ConstructPrivately& dummy)
		:mManagedInstance(nullptr)
	{

	}

	ManagedSerializableObject::ManagedSerializableObject(const ConstructPrivately& dummy, SPtr<ManagedSerializableObjectInfo> objInfo, MonoObject* managedInstance)
		:mManagedInstance(managedInstance), mObjInfo(objInfo)
	{

	}

	SPtr<ManagedSerializableObject> ManagedSerializableObject::createFromExisting(MonoObject* managedInstance)
	{
		if(managedInstance == nullptr)
			return nullptr;

		String elementNs;
		String elementTypeName;
		MonoUtil::getClassName(managedInstance, elementNs, elementTypeName);

		SPtr<ManagedSerializableObjectInfo> objInfo;
		if(!ScriptAssemblyManager::instance().getSerializableObjectInfo(elementNs, elementTypeName, objInfo))
			return nullptr;

		return bs_shared_ptr_new<ManagedSerializableObject>(ConstructPrivately(), objInfo, managedInstance);
	}

	SPtr<ManagedSerializableObject> ManagedSerializableObject::createNew(const SPtr<ManagedSerializableTypeInfoObject>& type)
	{
		SPtr<ManagedSerializableObjectInfo> currentObjInfo = nullptr;

		// See if this type even still exists
		if (!ScriptAssemblyManager::instance().getSerializableObjectInfo(type->mTypeNamespace, type->mTypeName, currentObjInfo))
			return nullptr;

		return bs_shared_ptr_new<ManagedSerializableObject>(ConstructPrivately(), currentObjInfo, createManagedInstance(type));
	}

	MonoObject* ManagedSerializableObject::createManagedInstance(const SPtr<ManagedSerializableTypeInfoObject>& type)
	{
		SPtr<ManagedSerializableObjectInfo> currentObjInfo = nullptr;

		// See if this type even still exists
		if (!ScriptAssemblyManager::instance().getSerializableObjectInfo(type->mTypeNamespace, type->mTypeName, currentObjInfo))
			return nullptr;

		// Never call constructor for structs. For classes we could call it if we could guarantee it always has one,
		// but at the moment we don't call constructor for them at all (which is probably fine).
		return currentObjInfo->mMonoClass->createInstance(false);
	}

	SPtr<ManagedSerializableObject> ManagedSerializableObject::createEmpty()
	{
		return bs_shared_ptr_new<ManagedSerializableObject>(ConstructPrivately());
	}

	void ManagedSerializableObject::serialize()
	{
		if (mManagedInstance == nullptr)
			return;

		mCachedData.clear();

		SPtr<ManagedSerializableObjectInfo> curType = mObjInfo;
		while (curType != nullptr)
		{
			for (auto& field : curType->mFields)
			{
				if (field.second->isSerializable())
				{
					ManagedSerializableFieldKey key(field.second->mParentTypeId, field.second->mFieldId);
					mCachedData[key] = getFieldData(field.second);
				}
			}

			curType = curType->mBaseClass;
		}

		// Serialize children
		for (auto& fieldEntry : mCachedData)
			fieldEntry.second->serialize();

		mManagedInstance = nullptr;
	}

	void ManagedSerializableObject::deserialize()
	{
		// See if this type even still exists
		SPtr<ManagedSerializableObjectInfo> currentObjInfo = nullptr;
		if (!ScriptAssemblyManager::instance().getSerializableObjectInfo(mObjInfo->mTypeInfo->mTypeNamespace, mObjInfo->mTypeInfo->mTypeName, currentObjInfo))
		{
			mManagedInstance = nullptr;
			mCachedData.clear();
			return;
		}

		deserialize(createManagedInstance(currentObjInfo->mTypeInfo), currentObjInfo);
	}

	void ManagedSerializableObject::deserialize(MonoObject* instance, const SPtr<ManagedSerializableObjectInfo>& objInfo)
	{
		mManagedInstance = instance;

		if (mManagedInstance == nullptr)
		{
			mCachedData.clear();
			return;
		}

		// Deserialize children
		for (auto& fieldEntry : mCachedData)
			fieldEntry.second->deserialize();

		// Scan all fields and ensure the fields still exist
		UINT32 i = 0;
		SPtr<ManagedSerializableObjectInfo> curType = mObjInfo;
		while (curType != nullptr)
		{
			for (auto& field : curType->mFields)
			{
				if (field.second->isSerializable())
				{
					UINT32 fieldId = field.second->mFieldId;
					UINT32 typeID = field.second->mParentTypeId;

					ManagedSerializableFieldKey key(typeID, fieldId);

					SPtr<ManagedSerializableMemberInfo> matchingFieldInfo = objInfo->findMatchingField(field.second, curType->mTypeInfo);
					if (matchingFieldInfo != nullptr)
						setFieldData(matchingFieldInfo, mCachedData[key]);

					i++;
				}
			}

			curType = curType->mBaseClass;
		}

		mObjInfo = objInfo;
		mCachedData.clear();
	}

	void ManagedSerializableObject::setFieldData(const SPtr<ManagedSerializableMemberInfo>& fieldInfo, const SPtr<ManagedSerializableFieldData>& val)
	{
		if (mManagedInstance != nullptr)
			fieldInfo->setValue(mManagedInstance, val->getValue(fieldInfo->mTypeInfo));
		else
		{
			ManagedSerializableFieldKey key(fieldInfo->mParentTypeId, fieldInfo->mFieldId);
			mCachedData[key] = val;
		}
	}

	SPtr<ManagedSerializableFieldData> ManagedSerializableObject::getFieldData(const SPtr<ManagedSerializableMemberInfo>& fieldInfo) const
	{
		if (mManagedInstance != nullptr)
		{
			MonoObject* fieldValue = fieldInfo->getValue(mManagedInstance);

			return ManagedSerializableFieldData::create(fieldInfo->mTypeInfo, fieldValue);
		}
		else
		{
			ManagedSerializableFieldKey key(fieldInfo->mParentTypeId, fieldInfo->mFieldId);
			auto iterFind = mCachedData.find(key);

			if (iterFind != mCachedData.end())
				return iterFind->second;

			return nullptr;
		}
	}

	RTTITypeBase* ManagedSerializableObject::getRTTIStatic()
	{
		return ManagedSerializableObjectRTTI::instance();
	}

	RTTITypeBase* ManagedSerializableObject::getRTTI() const
	{
		return ManagedSerializableObject::getRTTIStatic();
	}
}