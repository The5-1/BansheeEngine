//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsVulkanPrerequisites.h"
#include "RenderAPI/BsGpuParamBlockBuffer.h"

namespace bs { namespace ct
{
	/** @addtogroup Vulkan
	 *  @{
	 */

	/**	Vulkan implementation of a parameter block buffer (uniform buffer in Vulkan lingo). */
	class VulkanGpuParamBlockBuffer : public GpuParamBlockBuffer
	{
	public:
		VulkanGpuParamBlockBuffer(UINT32 size, GpuParamBlockUsage usage, GpuDeviceFlags deviceMask);
		~VulkanGpuParamBlockBuffer();

		/** @copydoc GpuParamBlockBuffer::writeToGPU */
		void writeToGPU(const UINT8* data, UINT32 queueIdx = 0) override;

		/** 
		 * Gets the resource wrapping the buffer object, on the specified device. If GPU param block buffer's device mask
		 * doesn't include the provided device, null is returned. 
		 */
		VulkanBuffer* getResource(UINT32 deviceIdx) const;
	protected:
		/** @copydoc GpuParamBlockBuffer::initialize */
		void initialize() override;

	private:
		VulkanHardwareBuffer* mBuffer;
		GpuDeviceFlags mDeviceMask;
	};

	/** @} */
}}