//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsVulkanPrerequisites.h"
#include "Image/BsTexture.h"
#include "RenderAPI/BsRenderTexture.h"

namespace bs
{
	/** @addtogroup Vulkan
	 *  @{
	 */

	/**
	 * Vulkan implementation of a render texture.
	 *
	 * @note	Sim thread only.
	 */
	class VulkanRenderTexture : public RenderTexture
	{
	public:
		virtual ~VulkanRenderTexture() { }

	protected:
		friend class VulkanTextureManager;

		VulkanRenderTexture(const RENDER_TEXTURE_DESC& desc);

		/** @copydoc RenderTexture::getProperties */
		const RenderTargetProperties& getPropertiesInternal() const override { return mProperties; }

		RenderTextureProperties mProperties;
	};

	namespace ct
	{
	/**
	 * Vulkan implementation of a render texture.
	 *
	 * @note	Core thread only.
	 */
	class VulkanRenderTexture : public RenderTexture
	{
	public:
		VulkanRenderTexture(const RENDER_TEXTURE_DESC& desc, UINT32 deviceIdx);
		virtual ~VulkanRenderTexture();

		/** @copydoc RenderTexture::getCustomAttribute */
		void getCustomAttribute(const String& name, void* data) const override;

	protected:
		/** @copydoc CoreObject::initialize() */
		void initialize() override;

		/** @copydoc RenderTexture::getProperties */
		const RenderTargetProperties& getPropertiesInternal() const override { return mProperties; }

		RenderTextureProperties mProperties;
		UINT32 mDeviceIdx;
		VulkanFramebuffer* mFramebuffer;
	};
		
	}

	/** @} */
}