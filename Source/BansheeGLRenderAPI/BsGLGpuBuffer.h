//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsGLPrerequisites.h"
#include "RenderAPI/BsGpuBuffer.h"
#include "BsGLBuffer.h"

namespace bs { namespace ct
{
	/** @addtogroup GL
	 *  @{
	 */

	/**	OpenGL implementation of a generic GPU buffer. */
	class GLGpuBuffer : public GpuBuffer
	{
	public:
		~GLGpuBuffer();

		/** @copydoc GpuBuffer::lock */
		void* lock(UINT32 offset, UINT32 length, GpuLockOptions options, UINT32 deviceIdx = 0, UINT32 queueIdx = 0) override;

		/** @copydoc GpuBuffer::unlock */
		void unlock() override;

		/** @copydoc GpuBuffer::readData */
		void readData(UINT32 offset, UINT32 length, void* dest, UINT32 deviceIdx = 0, UINT32 queueIdx = 0) override;

		/** @copydoc GpuBuffer::writeData */
		void writeData(UINT32 offset, UINT32 length, const void* source,
			BufferWriteType writeFlags = BWT_NORMAL, UINT32 queueIdx = 0) override;

		/** @copydoc GpuBuffer::copyData */
		void copyData(HardwareBuffer& srcBuffer, UINT32 srcOffset, UINT32 dstOffset, UINT32 length, 
			bool discardWholeBuffer = false, const SPtr<CommandBuffer>& commandBuffer = nullptr) override;

		/**	
		 * Returns internal OpenGL buffer ID. If binding the buffer to the pipeline, bind the texture using
		 * getGLTextureId() instead. 
		 */
		GLuint getGLBufferId() const { return mBuffer.getGLBufferId(); }

		/**	Returns internal OpenGL texture ID. */
		GLuint getGLTextureId() const { return mTextureID; }

		/** Returns the internal OpenGL format used by the elements of the buffer. */
		GLuint getGLFormat() const { return mFormat; }

	protected:
		friend class GLHardwareBufferManager;

		GLGpuBuffer(const GPU_BUFFER_DESC& desc, GpuDeviceFlags deviceMask);

		/** @copydoc GpuBuffer::initialize */
		void initialize() override;

		GLuint mTextureID;
		GLBuffer mBuffer;
		GLenum mFormat;
	};

	/** @} */
}}