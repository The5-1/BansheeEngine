//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsVulkanPrerequisites.h"
#include "Managers/BsRenderStateManager.h"

namespace bs { namespace ct
{
	/** @addtogroup Vulkan
	 *  @{
	 */

	/**	Handles creation of Vulkan pipeline states. */
	class VulkanRenderStateManager : public RenderStateManager
	{
	protected:
		/** @copydoc RenderStateManager::createSamplerStateInternal */
		SPtr<SamplerState> createSamplerStateInternal(const SAMPLER_STATE_DESC& desc,
			GpuDeviceFlags deviceMask) const override;

		/** @copydoc RenderStateManager::_createGraphicsPipelineState */
		SPtr<GraphicsPipelineState> _createGraphicsPipelineState(const PIPELINE_STATE_DESC& desc,
			GpuDeviceFlags deviceMask = GDF_DEFAULT) const override;

		/** @copydoc RenderStateManager::_createComputePipelineState */
		SPtr<ComputePipelineState> _createComputePipelineState(const SPtr<GpuProgram>& program,
			GpuDeviceFlags deviceMask = GDF_DEFAULT) const override;

		/** @copydoc RenderStateManager::_createPipelineParamInfo */
		SPtr<GpuPipelineParamInfo> _createPipelineParamInfo(const GPU_PIPELINE_PARAMS_DESC& desc,
			 GpuDeviceFlags deviceMask = GDF_DEFAULT) const override;
	};

	/** @} */
}}