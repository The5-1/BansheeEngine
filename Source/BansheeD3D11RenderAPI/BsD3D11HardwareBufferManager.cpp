//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsD3D11HardwareBufferManager.h"
#include "BsD3D11VertexBuffer.h"
#include "BsD3D11IndexBuffer.h"
#include "BsD3D11GpuBuffer.h"
#include "BsD3D11GpuParamBlockBuffer.h"
#include "RenderAPI/BsGpuParamDesc.h"

namespace bs { namespace ct
{
	D3D11HardwareBufferManager::D3D11HardwareBufferManager(D3D11Device& device)
		: mDevice(device)
	{ }

	SPtr<VertexBuffer> D3D11HardwareBufferManager::createVertexBufferInternal(const VERTEX_BUFFER_DESC& desc, 
		GpuDeviceFlags deviceMask)
	{
		SPtr<D3D11VertexBuffer> ret = bs_shared_ptr_new<D3D11VertexBuffer>(mDevice, desc, deviceMask);
		ret->_setThisPtr(ret);

		return ret;
	}

	SPtr<IndexBuffer> D3D11HardwareBufferManager::createIndexBufferInternal(const INDEX_BUFFER_DESC& desc, 
		GpuDeviceFlags deviceMask)
	{
		SPtr<D3D11IndexBuffer> ret = bs_shared_ptr_new<D3D11IndexBuffer>(mDevice, desc, deviceMask);
		ret->_setThisPtr(ret);

		return ret;
	}

	SPtr<GpuParamBlockBuffer> D3D11HardwareBufferManager::createGpuParamBlockBufferInternal(UINT32 size, 
		GpuParamBlockUsage usage, GpuDeviceFlags deviceMask)
	{
		D3D11GpuParamBlockBuffer* paramBlockBuffer = 
			new (bs_alloc<D3D11GpuParamBlockBuffer>()) D3D11GpuParamBlockBuffer(size, usage, deviceMask);

		SPtr<GpuParamBlockBuffer> paramBlockBufferPtr = bs_shared_ptr<D3D11GpuParamBlockBuffer>(paramBlockBuffer);
		paramBlockBufferPtr->_setThisPtr(paramBlockBufferPtr);

		return paramBlockBufferPtr;
	}

	SPtr<GpuBuffer> D3D11HardwareBufferManager::createGpuBufferInternal(const GPU_BUFFER_DESC& desc,
		GpuDeviceFlags deviceMask)
	{
		D3D11GpuBuffer* buffer = new (bs_alloc<D3D11GpuBuffer>()) 
			D3D11GpuBuffer(desc, deviceMask);

		SPtr<D3D11GpuBuffer> bufferPtr = bs_shared_ptr<D3D11GpuBuffer>(buffer);
		bufferPtr->_setThisPtr(bufferPtr);

		return bufferPtr;
	}
}}