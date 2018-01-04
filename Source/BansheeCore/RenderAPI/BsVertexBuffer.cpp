//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "RenderAPI/BsVertexBuffer.h"
#include "Managers/BsHardwareBufferManager.h"

namespace bs 
{
	VertexBufferProperties::VertexBufferProperties(UINT32 numVertices, UINT32 vertexSize)
		:mNumVertices(numVertices), mVertexSize(vertexSize)
	{ }

	VertexBuffer::VertexBuffer(const VERTEX_BUFFER_DESC& desc)
		: mProperties(desc.numVerts, desc.vertexSize), mUsage(desc.usage), mStreamOut(desc.streamOut)
    {

    }

	SPtr<ct::CoreObject> VertexBuffer::createCore() const
	{
		VERTEX_BUFFER_DESC desc;
		desc.vertexSize = mProperties.mVertexSize;
		desc.numVerts = mProperties.mNumVertices;
		desc.usage = mUsage;
		desc.streamOut = mStreamOut;

		return ct::HardwareBufferManager::instance().createVertexBufferInternal(desc);
	}

	SPtr<ct::VertexBuffer> VertexBuffer::getCore() const
	{
		return std::static_pointer_cast<ct::VertexBuffer>(mCoreSpecific);
	}

	SPtr<VertexBuffer> VertexBuffer::create(const VERTEX_BUFFER_DESC& desc)
	{
		return HardwareBufferManager::instance().createVertexBuffer(desc);
	}

	namespace ct
	{
	VertexBuffer::VertexBuffer(const VERTEX_BUFFER_DESC& desc, GpuDeviceFlags deviceMask)
		:HardwareBuffer(desc.vertexSize * desc.numVerts), mProperties(desc.numVerts, desc.vertexSize)
	{ }

	SPtr<VertexBuffer> VertexBuffer::create(const VERTEX_BUFFER_DESC& desc, GpuDeviceFlags deviceMask)
	{
		return HardwareBufferManager::instance().createVertexBuffer(desc, deviceMask);
	}
	}
}
