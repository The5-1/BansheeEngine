//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Components/BsCSliderJoint.h"
#include "Scene/BsSceneObject.h"
#include "Components/BsCRigidbody.h"
#include "RTTI/BsCSliderJointRTTI.h"

namespace bs
{
	CSliderJoint::CSliderJoint()
		: CJoint(mDesc)
	{ }

	CSliderJoint::CSliderJoint(const HSceneObject& parent)
		: CJoint(parent, mDesc)
	{
		setName("SliderJoint");
	}

	float CSliderJoint::getPosition() const
	{
		if (mInternal == nullptr)
			return 0.0f;

		return _getInternal()->getPosition();
	}

	float CSliderJoint::getSpeed() const
	{
		if (mInternal == nullptr)
			return 0.0f;

		return _getInternal()->getSpeed();
	}

	LimitLinearRange CSliderJoint::getLimit() const
	{
		return mDesc.limit;
	}

	void CSliderJoint::setLimit(const LimitLinearRange& limit)
	{
		if (mDesc.limit == limit)
			return;

		mDesc.limit = limit;

		if (mInternal != nullptr)
			_getInternal()->setLimit(limit);
	}

	void CSliderJoint::setFlag(SliderJointFlag flag, bool enabled)
	{
		bool isEnabled = ((UINT32)mDesc.flag & (UINT32)flag) != 0;
		if (isEnabled == enabled)
			return;

		if (enabled)
			mDesc.flag = (SliderJointFlag)((UINT32)mDesc.flag | (UINT32)flag);
		else
			mDesc.flag = (SliderJointFlag)((UINT32)mDesc.flag & ~(UINT32)flag);

		if (mInternal != nullptr)
			_getInternal()->setFlag(flag, enabled);
	}

	bool CSliderJoint::hasFlag(SliderJointFlag flag) const
	{
		return ((UINT32)mDesc.flag & (UINT32)flag) != 0;
	}

	SPtr<Joint> CSliderJoint::createInternal()
	{
		SPtr<Joint> joint = SliderJoint::create(mDesc);

		joint->_setOwner(PhysicsOwnerType::Component, this);
		return joint;
	}

	void CSliderJoint::getLocalTransform(JointBody body, Vector3& position, Quaternion& rotation)
	{
		position = mPositions[(int)body];
		rotation = mRotations[(int)body];

		HRigidbody rigidbody = mBodies[(int)body];
		const Transform& tfrm = SO()->getTransform();
		if (rigidbody == nullptr) // Get world space transform if no relative to any body
		{
			Quaternion worldRot = tfrm.getRotation();

			rotation = worldRot*rotation;
			position = worldRot.rotate(position) + tfrm.getPosition();
		}
		else
		{
			const Transform& rigidbodyTfrm = rigidbody->SO()->getTransform();

			// Use only the offset for positioning, but for rotation use both the offset and target SO rotation.
			// (Needed because we need to rotate the joint SO in order to orient the slider direction, so we need an
			// additional transform that allows us to orient the object)
			position = rotation.rotate(position);
			rotation = (rigidbodyTfrm.getRotation()*rotation).inverse()*tfrm.getRotation();
		}
	}

	RTTITypeBase* CSliderJoint::getRTTIStatic()
	{
		return CSliderJointRTTI::instance();
	}

	RTTITypeBase* CSliderJoint::getRTTI() const
	{
		return CSliderJoint::getRTTIStatic();
	}
}