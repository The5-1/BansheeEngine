//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsGLHardwareBufferManager.h"
#include "BsGLVertexBuffer.h"
#include "BsGLVertexArrayObjectManager.h"
#include "Profiling/BsRenderStats.h"
#include "BsGLCommandBuffer.h"

namespace bs { namespace ct
{
	GLVertexBuffer::GLVertexBuffer(const VERTEX_BUFFER_DESC& desc, GpuDeviceFlags deviceMask)
		:VertexBuffer(desc, deviceMask), mUsage(desc.usage)
	{
		assert((deviceMask == GDF_DEFAULT || deviceMask == GDF_PRIMARY) && "Multiple GPUs not supported natively on OpenGL.");
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		while (mVAObjects.size() > 0)
			GLVertexArrayObjectManager::instance().notifyBufferDestroyed(mVAObjects[0]);

		BS_INC_RENDER_STAT_CAT(ResDestroyed, RenderStatObject_VertexBuffer);
	}

	void GLVertexBuffer::initialize()
	{
		mBuffer.initialize(GL_ARRAY_BUFFER, mSize, mUsage);
		
		BS_INC_RENDER_STAT_CAT(ResCreated, RenderStatObject_VertexBuffer);
		VertexBuffer::initialize();
	}

	void GLVertexBuffer::registerVAO(const GLVertexArrayObject& vao)
	{
		mVAObjects.push_back(vao);
	}

	void GLVertexBuffer::unregisterVAO(const GLVertexArrayObject& vao)
	{
		auto iterFind = std::find(mVAObjects.begin(), mVAObjects.end(), vao);

		if (iterFind != mVAObjects.end())
			mVAObjects.erase(iterFind);
	}

	void* GLVertexBuffer::map(UINT32 offset, UINT32 length, GpuLockOptions options, UINT32 deviceIdx, UINT32 queueIdx)
	{
		return mBuffer.lock(offset, length, options);
	}

	void GLVertexBuffer::unmap()
	{
		mBuffer.unlock();
	}

	void GLVertexBuffer::readData(UINT32 offset, UINT32 length, void* dest, UINT32 deviceIdx, UINT32 queueIdx)
	{
		mBuffer.readData(offset, length, dest);
	}

	void GLVertexBuffer::writeData(UINT32 offset, UINT32 length,
		const void* pSource, BufferWriteType writeFlags, UINT32 queueIdx)
	{
		mBuffer.writeData(offset, length, pSource, writeFlags);
	}

	void GLVertexBuffer::copyData(HardwareBuffer& srcBuffer, UINT32 srcOffset,
		UINT32 dstOffset, UINT32 length, bool discardWholeBuffer, const SPtr<ct::CommandBuffer>& commandBuffer)
	{
		auto executeRef = [this](HardwareBuffer& srcBuffer, UINT32 srcOffset, UINT32 dstOffset, UINT32 length)
		{
			GLVertexBuffer& glSrcBuffer = static_cast<GLVertexBuffer&>(srcBuffer);
			glSrcBuffer.mBuffer.copyData(mBuffer, srcOffset, dstOffset, length);
		};

		if (commandBuffer == nullptr)
			executeRef(srcBuffer, srcOffset, dstOffset, length);
		else
		{
			auto execute = [&]() { executeRef(srcBuffer, srcOffset, dstOffset, length); };

			SPtr<GLCommandBuffer> cb = std::static_pointer_cast<GLCommandBuffer>(commandBuffer);
			cb->queueCommand(execute);
		}
	}
}}
