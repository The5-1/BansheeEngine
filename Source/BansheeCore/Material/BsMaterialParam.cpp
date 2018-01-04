//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Material/BsMaterialParam.h"
#include "Math/BsVector2I.h"
#include "Material/BsMaterialParams.h"
#include "Material/BsMaterial.h"

namespace bs
{
	template<class T, bool Core>
	TMaterialDataParam<T, Core>::TMaterialDataParam(const String& name, const MaterialPtrType& material)
		:mParamIndex(0), mArraySize(0), mMaterial(nullptr)
	{
		if(material != nullptr)
		{
			SPtr<MaterialParamsType> params = material->_getInternalParams();

			UINT32 paramIndex;
			auto result = params->getParamIndex(name, MaterialParams::ParamType::Data, 
				(GpuParamDataType)TGpuDataParamInfo<T>::TypeId, 0, paramIndex);

			if (result == MaterialParams::GetParamResult::Success)
			{
				const MaterialParams::ParamData* data = params->getParamData(paramIndex);

				mMaterial = material;
				mParamIndex = paramIndex;
				mArraySize = data->arraySize;
			}
			else
				params->reportGetParamError(result, name, 0);
		}
	}

	template<class T, bool Core>
	void TMaterialDataParam<T, Core>::set(const T& value, UINT32 arrayIdx) const
	{
		if (mMaterial == nullptr)
			return;

		if(arrayIdx >= mArraySize)
		{
			LOGWRN("Array index out of range. Provided index was " + toString(arrayIdx) + 
				" but array length is " + toString(mArraySize));
			return;
		}

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		params->setDataParam(*data, arrayIdx, value);
		mMaterial->_markCoreDirty();
	}

	template<class T, bool Core>
	T TMaterialDataParam<T, Core>::get(UINT32 arrayIdx) const
	{
		T output{};
		if (mMaterial == nullptr || arrayIdx >= mArraySize)
			return output;

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		params->getDataParam(*data, arrayIdx, output);
		return output;
	}

	template<bool Core>
	TMaterialParamStruct<Core>::TMaterialParamStruct(const String& name, const MaterialPtrType& material)
		:mParamIndex(0), mArraySize(0), mMaterial(nullptr)
	{
		if (material != nullptr)
		{
			SPtr<MaterialParamsType> params = material->_getInternalParams();

			UINT32 paramIndex;
			auto result = params->getParamIndex(name, MaterialParams::ParamType::Data, GPDT_STRUCT, 0, paramIndex);

			if (result == MaterialParams::GetParamResult::Success)
			{
				const MaterialParams::ParamData* data = params->getParamData(paramIndex);

				mMaterial = material;
				mParamIndex = paramIndex;
				mArraySize = data->arraySize;
			}
			else
				params->reportGetParamError(result, name, 0);
		}
	}

	template<bool Core>
	void TMaterialParamStruct<Core>::set(const void* value, UINT32 sizeBytes, UINT32 arrayIdx) const
	{
		if (mMaterial == nullptr)
			return;

		if (arrayIdx >= mArraySize)
		{
			LOGWRN("Array index out of range. Provided index was " + toString(arrayIdx) +
				" but array length is " + toString(mArraySize));
			return;
		}

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		params->setStructData(*data, value, sizeBytes, arrayIdx);
		mMaterial->_markCoreDirty();
	}

	template<bool Core>
	void TMaterialParamStruct<Core>::get(void* value, UINT32 sizeBytes, UINT32 arrayIdx) const
	{
		if (mMaterial == nullptr || arrayIdx >= mArraySize)
			return;

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		params->getStructData(*data, value, sizeBytes, arrayIdx);
	}

	template<bool Core>
	UINT32 TMaterialParamStruct<Core>::getElementSize() const
	{
		if (mMaterial == nullptr)
			return 0;

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		return params->getStructSize(*data);
	}

	template<bool Core>
	TMaterialParamTexture<Core>::TMaterialParamTexture(const String& name, const MaterialPtrType& material)
		:mParamIndex(0), mMaterial(nullptr)
	{
		if (material != nullptr)
		{
			SPtr<MaterialParamsType> params = material->_getInternalParams();

			UINT32 paramIndex;
			auto result = params->getParamIndex(name, MaterialParams::ParamType::Texture, GPDT_UNKNOWN, 0, paramIndex);

			if (result == MaterialParams::GetParamResult::Success)
			{
				mMaterial = material;
				mParamIndex = paramIndex;
			}
			else
				params->reportGetParamError(result, name, 0);
		}
	}

	template<bool Core>
	void TMaterialParamTexture<Core>::set(const TextureType& texture, const TextureSurface& surface) const
	{
		if (mMaterial == nullptr)
			return;

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		// If there is a default value, assign that instead of null
		TextureType newValue = texture;
		if (newValue == nullptr)
			params->getDefaultTexture(*data, newValue);

		params->setTexture(*data, newValue, surface);
		mMaterial->_markCoreDirty();
		mMaterial->_markDependenciesDirty();
		mMaterial->_markResourcesDirty();
	}

	template<bool Core>
	typename TMaterialParamTexture<Core>::TextureType TMaterialParamTexture<Core>::get() const
	{
		TextureType texture;
		if (mMaterial == nullptr)
			return texture;

		TextureSurface surface;

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		params->getTexture(*data, texture, surface);
		return texture;
	}
	
	template<bool Core>
	TMaterialParamLoadStoreTexture<Core>::TMaterialParamLoadStoreTexture(const String& name, 
		const MaterialPtrType& material)
		:mParamIndex(0), mMaterial(nullptr)
	{
		if (material != nullptr)
		{
			SPtr<MaterialParamsType> params = material->_getInternalParams();

			UINT32 paramIndex;
			auto result = params->getParamIndex(name, MaterialParams::ParamType::Texture, GPDT_UNKNOWN, 0, paramIndex);

			if (result == MaterialParams::GetParamResult::Success)
			{
				mMaterial = material;
				mParamIndex = paramIndex;
			}
			else
				params->reportGetParamError(result, name, 0);
		}
	}

	template<bool Core>
	void TMaterialParamLoadStoreTexture<Core>::set(const TextureType& texture, const TextureSurface& surface) const
	{
		if (mMaterial == nullptr)
			return;

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		params->setLoadStoreTexture(*data, texture, surface);
		mMaterial->_markCoreDirty();
		mMaterial->_markDependenciesDirty();
		mMaterial->_markResourcesDirty();
	}

	template<bool Core>
	typename TMaterialParamLoadStoreTexture<Core>::TextureType TMaterialParamLoadStoreTexture<Core>::get() const
	{
		TextureType texture;
		if (mMaterial == nullptr)
			return texture;

		TextureSurface surface;

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		params->getLoadStoreTexture(*data, texture, surface);

		return texture;
	}
	
	template<bool Core>
	TMaterialParamBuffer<Core>::TMaterialParamBuffer(const String& name, const MaterialPtrType& material)
		:mParamIndex(0), mMaterial(nullptr)
	{
		if (material != nullptr)
		{
			SPtr<MaterialParamsType> params = material->_getInternalParams();

			UINT32 paramIndex;
			auto result = params->getParamIndex(name, MaterialParams::ParamType::Buffer, GPDT_UNKNOWN, 0, paramIndex);

			if (result == MaterialParams::GetParamResult::Success)
			{
				mMaterial = material;
				mParamIndex = paramIndex;
			}
			else
				params->reportGetParamError(result, name, 0);
		}
	}

	template<bool Core>
	void TMaterialParamBuffer<Core>::set(const BufferType& buffer) const
	{
		if (mMaterial == nullptr)
			return;

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		params->setBuffer(*data, buffer);
		mMaterial->_markCoreDirty();
		mMaterial->_markDependenciesDirty();
	}

	template<bool Core>
	typename TMaterialParamBuffer<Core>::BufferType TMaterialParamBuffer<Core>::get() const
	{
		BufferType buffer;
		if (mMaterial == nullptr)
			return buffer;

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);
		params->getBuffer(*data, buffer);

		return buffer;
	}

	template<bool Core>
	TMaterialParamSampState<Core>::TMaterialParamSampState(const String& name, const MaterialPtrType& material)
		:mParamIndex(0), mMaterial(nullptr)
	{
		if (material != nullptr)
		{
			SPtr<MaterialParamsType> params = material->_getInternalParams();

			UINT32 paramIndex;
			auto result = params->getParamIndex(name, MaterialParams::ParamType::Sampler, GPDT_UNKNOWN, 0, paramIndex);

			if (result == MaterialParams::GetParamResult::Success)
			{
				mMaterial = material;
				mParamIndex = paramIndex;
			}
			else
				params->reportGetParamError(result, name, 0);
		}
	}

	template<bool Core>
	void TMaterialParamSampState<Core>::set(const SamplerStateType& sampState) const
	{
		if (mMaterial == nullptr)
			return;

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		// If there is a default value, assign that instead of null
		SamplerStateType newValue = sampState;
		if (newValue == nullptr)
			params->getDefaultSamplerState(*data, newValue);

		params->setSamplerState(*data, newValue);
		mMaterial->_markCoreDirty();
		mMaterial->_markDependenciesDirty();
	}

	template<bool Core>
	typename TMaterialParamSampState<Core>::SamplerStateType TMaterialParamSampState<Core>::get() const
	{
		SamplerStateType samplerState;
		if (mMaterial == nullptr)
			return samplerState;

		SPtr<MaterialParamsType> params = mMaterial->_getInternalParams();
		const MaterialParams::ParamData* data = params->getParamData(mParamIndex);

		params->getSamplerState(*data, samplerState);
		return samplerState;
	}

	template class TMaterialDataParam<float, false>;
	template class TMaterialDataParam<int, false>;
	template class TMaterialDataParam<Color, false>;
	template class TMaterialDataParam<Vector2, false>;
	template class TMaterialDataParam<Vector3, false>;
	template class TMaterialDataParam<Vector4, false>;
	template class TMaterialDataParam<Vector2I, false>;
	template class TMaterialDataParam<Vector3I, false>;
	template class TMaterialDataParam<Vector4I, false>;
	template class TMaterialDataParam<Matrix2, false>;
	template class TMaterialDataParam<Matrix2x3, false>;
	template class TMaterialDataParam<Matrix2x4, false>;
	template class TMaterialDataParam<Matrix3, false>;
	template class TMaterialDataParam<Matrix3x2, false>;
	template class TMaterialDataParam<Matrix3x4, false>;
	template class TMaterialDataParam<Matrix4, false>;
	template class TMaterialDataParam<Matrix4x2, false>;
	template class TMaterialDataParam<Matrix4x3, false>;

	template class TMaterialDataParam<float, true>;
	template class TMaterialDataParam<int, true>;
	template class TMaterialDataParam<Color, true>;
	template class TMaterialDataParam<Vector2, true>;
	template class TMaterialDataParam<Vector3, true>;
	template class TMaterialDataParam<Vector4, true>;
	template class TMaterialDataParam<Vector2I, true>;
	template class TMaterialDataParam<Vector3I, true>;
	template class TMaterialDataParam<Vector4I, true>;
	template class TMaterialDataParam<Matrix2, true>;
	template class TMaterialDataParam<Matrix2x3, true>;
	template class TMaterialDataParam<Matrix2x4, true>;
	template class TMaterialDataParam<Matrix3, true>;
	template class TMaterialDataParam<Matrix3x2, true>;
	template class TMaterialDataParam<Matrix3x4, true>;
	template class TMaterialDataParam<Matrix4, true>;
	template class TMaterialDataParam<Matrix4x2, true>;
	template class TMaterialDataParam<Matrix4x3, true>;

	template class TMaterialParamStruct<false>;
	template class TMaterialParamStruct<true>;

	template class TMaterialParamTexture<false>;
	template class TMaterialParamTexture<true>;

	template class TMaterialParamLoadStoreTexture<false>;
	template class TMaterialParamLoadStoreTexture<true>;

	template class TMaterialParamBuffer<false>;
	template class TMaterialParamBuffer<true>;

	template class TMaterialParamSampState<false>;
	template class TMaterialParamSampState<true>;
}