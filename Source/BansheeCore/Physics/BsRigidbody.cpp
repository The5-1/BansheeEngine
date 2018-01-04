//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Physics/BsRigidbody.h"
#include "Physics/BsPhysics.h"
#include "Scene/BsSceneObject.h"

namespace bs
{
	Rigidbody::Rigidbody(const HSceneObject& linkedSO)
		:mLinkedSO(linkedSO)
	{

	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::_setTransform(const Vector3& position, const Quaternion& rotation)
	{
		mLinkedSO->setWorldPosition(position);
		mLinkedSO->setWorldRotation(rotation);
	}

	SPtr<Rigidbody> Rigidbody::create(const HSceneObject& linkedSO)
	{
		return gPhysics().createRigidbody(linkedSO);
	}
}