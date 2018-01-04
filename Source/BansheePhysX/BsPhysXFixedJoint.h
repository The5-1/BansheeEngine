//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsPhysXPrerequisites.h"
#include "Physics/BsFixedJoint.h"
#include "PxPhysics.h"

namespace bs
{
	/** @addtogroup PhysX
	 *  @{
	 */

	/** PhysX implementation of a FixedJoint. */
	class PhysXFixedJoint : public FixedJoint
	{
	public:
		PhysXFixedJoint(physx::PxPhysics* physx, const FIXED_JOINT_DESC& desc);
		~PhysXFixedJoint();
	};

	/** @} */
}