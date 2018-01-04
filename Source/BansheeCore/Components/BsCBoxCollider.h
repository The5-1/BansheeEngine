//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsCorePrerequisites.h"
#include "Physics/BsBoxCollider.h"
#include "Components/BsCCollider.h"

namespace bs 
{
	/** @addtogroup Components-Core
	 *  @{
	 */

	/**
	 * @copydoc	BoxCollider
	 *
	 * @note Wraps BoxCollider as a Component.
	 */
	class BS_CORE_EXPORT BS_SCRIPT_EXPORT(m:Physics,n:BoxCollider) CBoxCollider : public CCollider
	{
	public:
		CBoxCollider(const HSceneObject& parent, const Vector3& extents = Vector3::ONE);

		/** @copydoc BoxCollider::setExtents */
		BS_SCRIPT_EXPORT(n:Extents,pr:setter)
		void setExtents(const Vector3& extents);

		/** @copydoc BoxCollider::getExtents */
		BS_SCRIPT_EXPORT(n:Extents,pr:getter)
		Vector3 getExtents() const { return mExtents; }

		/** Determines the position of the box shape, relative to the component's scene object. */
		BS_SCRIPT_EXPORT(n:Center,pr:setter)
		void setCenter(const Vector3& center);

		/** @copydoc setCenter() */
		BS_SCRIPT_EXPORT(n:Center,pr:getter)
		Vector3 getCenter() const { return mLocalPosition; }

		/** @name Internal
		 *  @{
		 */

		/**	Returns the box collider that this component wraps. */
		BoxCollider* _getInternal() const { return static_cast<BoxCollider*>(mInternal.get()); }

		/** @} */

		/************************************************************************/
		/* 						COMPONENT OVERRIDES                      		*/
		/************************************************************************/
	protected:
		friend class SceneObject;

		/** @copydoc CCollider::createInternal */
		SPtr<Collider> createInternal() override;

	protected:
		Vector3 mExtents = Vector3::ZERO;

		/************************************************************************/
		/* 								RTTI		                     		*/
		/************************************************************************/
	public:
		friend class CBoxColliderRTTI;
		static RTTITypeBase* getRTTIStatic();
		RTTITypeBase* getRTTI() const override;

	protected:
		CBoxCollider() {} // Serialization only
	};

	 /** @} */
}