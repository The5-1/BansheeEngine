//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsCorePrerequisites.h"
#include "Reflection/BsRTTIType.h"
#include "Components/BsCCamera.h"
#include "RTTI/BsGameObjectRTTI.h"

namespace bs
{
	/** @cond RTTI */
	/** @addtogroup RTTI-Impl-Engine
	 *  @{
	 */

	class BS_CORE_EXPORT CCameraRTTI : public RTTIType<CCamera, Component, CCameraRTTI>
	{
	private:
		SPtr<Camera> getInternal(CCamera* obj) { return obj->mInternal; }
		void setInternal(CCamera* obj, SPtr<Camera> val) { obj->mInternal = val; }

	public:
		CCameraRTTI()
		{
			addReflectablePtrField("mInternal", 0, &CCameraRTTI::getInternal, &CCameraRTTI::setInternal);
		}

		const String& getRTTIName() override
		{
			static String name = "CCamera";
			return name;
		}

		UINT32 getRTTIId() override
		{
			return TID_CCamera;
		}

		SPtr<IReflectable> newRTTIObject() override
		{
			return GameObjectRTTI::createGameObject<CCamera>();
		}
	};

	/** @} */
	/** @endcond */
}