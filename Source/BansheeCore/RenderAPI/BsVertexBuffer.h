//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsCorePrerequisites.h"
#include "RenderAPI/BsHardwareBuffer.h"
#include "CoreThread/BsCoreObject.h"

namespace bs 
{
	/** @addtogroup RenderAPI
	 *  @{
	 */

	/** Descriptor structure used for initialization of a VertexBuffer. */
	struct VERTEX_BUFFER_DESC
	{
		UINT32 vertexSize; /**< Size of a single vertex in the buffer, in bytes. */
		UINT32 numVerts; /**< Number of vertices the buffer can hold. */
		GpuBufferUsage usage = GBU_STATIC; /**< Usage that tells the hardware how will be buffer be used. */
		bool streamOut = false; /**< If true the buffer will be usable for streaming out data from the GPU. */
	};

	/** Contains information about a vertex buffer buffer. */
	class BS_CORE_EXPORT VertexBufferProperties
	{
	public:
		VertexBufferProperties(UINT32 numVertices, UINT32 vertexSize);

		/**	Gets the size in bytes of a single vertex in this buffer. */
        UINT32 getVertexSize() const { return mVertexSize; }

		/**	Get the number of vertices in this buffer. */
        UINT32 getNumVertices() const { return mNumVertices; }

	protected:
		friend class VertexBuffer;
		friend class ct::VertexBuffer;

		UINT32 mNumVertices;
		UINT32 mVertexSize;
	};

	/**	Specialization of a hardware buffer used for holding vertex data. */
    class BS_CORE_EXPORT VertexBuffer : public CoreObject
    {
	public:
		virtual ~VertexBuffer() { }

		/**
		 * Retrieves a core implementation of a vertex buffer usable only from the core thread.
		 *
		 * @note	Core thread only.
		 */
		SPtr<ct::VertexBuffer> getCore() const;

		/** @copydoc HardwareBufferManager::createVertexBuffer */
		static SPtr<VertexBuffer> create(const VERTEX_BUFFER_DESC& desc);

		static const int MAX_SEMANTIC_IDX = 8;
	protected:
		friend class HardwareBufferManager;

		VertexBuffer(const VERTEX_BUFFER_DESC& desc);

		/** @copydoc CoreObject::createCore */
		virtual SPtr<ct::CoreObject> createCore() const;

	protected:
		VertexBufferProperties mProperties;
		GpuBufferUsage mUsage;
		bool mStreamOut;
    };

	/** @} */

	namespace ct
	{
	/** @addtogroup RenderAPI-Internal
	 *  @{
	 */

	/** Core thread specific implementation of a bs::VertexBuffer. */
	class BS_CORE_EXPORT VertexBuffer : public CoreObject, public HardwareBuffer
	{
	public:
		VertexBuffer(const VERTEX_BUFFER_DESC& desc, GpuDeviceFlags deviceMask = GDF_DEFAULT);
		virtual ~VertexBuffer() { }

		/**	Returns information about the vertex buffer. */
		const VertexBufferProperties& getProperties() const { return mProperties; }

		/** @copydoc HardwareBufferManager::createVertexBuffer */
		static SPtr<VertexBuffer> create(const VERTEX_BUFFER_DESC& desc, GpuDeviceFlags deviceMask = GDF_DEFAULT);

	protected:
		VertexBufferProperties mProperties;
	};

	/** @} */
		}
}