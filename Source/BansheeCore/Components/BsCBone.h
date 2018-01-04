//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsCorePrerequisites.h"
#include "Scene/BsComponent.h"

namespace bs 
{
	/** @addtogroup Components
	 *  @{
	 */

	/**
	 * Component that maps animation for specific bone also be applied to the SceneObject this component is attached to. 
	 * The component will attach to the first found parent Animation component.
	 */
	class BS_CORE_EXPORT BS_SCRIPT_EXPORT(m:Animation,n:Bone) CBone : public Component
	{
	public:
		CBone(const HSceneObject& parent);
		virtual ~CBone() {}
		
		/** Determines the name of the bone the component is referencing. */
		BS_SCRIPT_EXPORT(n:Name,pr:setter)
		void setBoneName(const String& name);

		/** @copydoc setBoneName */
		BS_SCRIPT_EXPORT(n:Name,pr:getter)
		const String& getBoneName() const { return mBoneName; }

		/** @name Internal
		 *  @{
		 */

		/**
		 * Changes the parent animation of this component.
		 *
		 * @param[in]	animation	New animation parent, can be null.
		 * @param[in]	isInternal	If true the bone will just be changed internally, but parent animation will not be
		 *							notified.
		 */
		void _setParent(const HAnimation& animation, bool isInternal = false);

		/** @} */
	private:
		/** Attempts to find the parent Animation component and registers itself with it. */
		void updateParentAnimation();

		/************************************************************************/
		/* 						COMPONENT OVERRIDES                      		*/
		/************************************************************************/
	protected:
		friend class SceneObject;

		/** @copydoc Component::onDestroyed() */
		void onDestroyed() override;

		/** @copydoc Component::onDisabled() */
		void onDisabled() override;

		/** @copydoc Component::onEnabled() */
		void onEnabled() override;

		/** @copydoc Component::onTransformChanged() */
		void onTransformChanged(TransformChangedFlags flags) override;
	protected:
		using Component::destroyInternal;

		String mBoneName;
		HAnimation mParent;

		/************************************************************************/
		/* 								RTTI		                     		*/
		/************************************************************************/
	public:
		friend class CBoneRTTI;
		static RTTITypeBase* getRTTIStatic();
		RTTITypeBase* getRTTI() const override;

	protected:
		CBone(); // Serialization only
	 };

	 /** @} */
}