#pragma once

#include "BsPrerequisites.h"
#include "BsIReflectable.h"
#include "BsVector3.h"
#include "BsQuaternion.h"
#include "BsColor.h"
#include "BsSphere.h"
#include "BsCoreObject.h"

namespace BansheeEngine
{
	/** Light type that determines how is light information parsed by the renderer and other systems. */
	enum class LightType
	{
		Directional, 
		Point, 
		Spot
	};

	/**	Signals which portion of a LightInternal is dirty. */
	enum class LightDirtyFlag
	{
		Transform = 0x01,
		Everything = 0x02
	};

	/**
	 * Illuminates a portion of the scene covered by a light. Base class for both sim and core thread Light implementations.
	 */
	class BS_EXPORT LightBase
	{
	public:
		LightBase();
		LightBase(LightType type, Color color, float intensity, float range, 
			bool castsShadows, Degree spotAngle, Degree spotFalloffAngle);

		virtual ~LightBase() { }

		/**	Returns the position of the light, in world space. */
		Vector3 getPosition() const { return mPosition; }

		/**	Sets the position of the light, in world space. */
		void setPosition(const Vector3& position) { mPosition = position; _markCoreDirty(); updateBounds(); }

		/**	Returns the rotation of the light, in world space. */
		Quaternion getRotation() const { return mRotation; }

		/**	Sets the rotation of the light, in world space. */
		void setRotation(const Quaternion& rotation) { mRotation = rotation; _markCoreDirty(); updateBounds(); }

		/**	Returns the type of the light. */
		LightType getType() const { return mType; }

		/**	Changes the type of the light. */
		void setType(LightType type) { mType = type; _markCoreDirty(); updateBounds(); }

		/**	Checks does this light cast shadows when rendered. */
		bool getCastsShadow() const { return mCastsShadows; }

		/**	Sets whether this light will cast shadows when rendered. */
		void setCastsShadow(bool castsShadow) { mCastsShadows = castsShadow; _markCoreDirty(); }

		/**	Returns the color emitted from the light. */
		Color getColor() const { return mColor; }

		/**	Sets the color emitted from the light. */
		void setColor(const Color& color) { mColor = color; _markCoreDirty(); }

		/**	Returns the maximum range of the light. Light will not affect any geometry past that point. */
		float getRange() const { return mRange; }

		/**
		 * Returns the maximum range of the light. Light will not affect any geometry past that point.
		 *
		 * @note	Normally you want to set this at a point where light intensity is too low due to attenuation.
		 */
		void setRange(float range) { mRange = range; _markCoreDirty(); updateBounds(); }

		/**
		 * Gets the power of the light source. This is luminous flux for point & spot lights, and radiance for directional 
		 * lights.
		 */
		float getIntensity() const { return mIntensity; }

		/**
		 * Sets the power of the light source. This will be luminous flux for point & spot lights, and radiance for 
		 * directional lights.
		 */
		void setIntensity(float intensity) { mIntensity = intensity; _markCoreDirty(); }

		/**	Gets the total angle covered by a spot light. */
		Degree getSpotAngle() const { return mSpotAngle; }

		/**	Sets the total angle covered by a spot light. */
		void setSpotAngle(const Degree& spotAngle) { mSpotAngle = spotAngle; _markCoreDirty(); updateBounds(); }

		/**
		 * Gets the falloff angle covered by a spot light. Falloff angle determines at what point does light intensity 
		 * starts quadratically falling off as the angle approaches the total spot angle.
		 */
		Degree getSpotFalloffAngle() const { return mSpotFalloffAngle; }

		/**
		 * Sets the falloff angle covered by a spot light. Falloff angle determines at what point does light intensity 
		 * starts quadratically falling off as the angle approaches the total spot angle.
		 */
		void setSpotFalloffAngle(const Degree& spotFallofAngle) 
		{ mSpotFalloffAngle = spotFallofAngle; _markCoreDirty(); updateBounds(); }

		/**	Returns world space bounds that completely encompass the light's area of influence. */
		Sphere getBounds() const { return mBounds; }

		/**
		 * Returns the radiance of the light source. This is the value that should be used in lighting equations.
		 *
		 * @note	
		 * Ignores the light direction, therefore caller must ensure to properly handle non-uniform emitters like spot 
		 * lights.
		 */
		float getRadiance() const;

		/**	Checks whether the light should be rendered or not. */
		bool getIsActive() const { return mIsActive; }

		/**	Sets whether the light should be rendered or not. */
		void setIsActive(bool active) { mIsActive = active; _markCoreDirty(); }

		/** @copydoc CoreObject::markCoreDirty */
		virtual void _markCoreDirty(LightDirtyFlag flag = LightDirtyFlag::Everything) { }

	protected:
		/** Updates the internal bounds for the light. Call this whenever a property affecting the bounds changes. */
		void updateBounds();

		Vector3 mPosition; /**< World space position. */
		Quaternion mRotation; /**< World space rotation. */

		LightType mType; /**< Type of light that determines how are the rest of the parameters interpreted. */
		bool mCastsShadows; /**< Determines whether the light casts shadows. */
		Color mColor; /**< Color of the light. */
		float mRange; /**< Cut off range for the light when rendering. */
		float mIntensity; /**< Power of the light source. This will be luminous flux for point & spot lights, and radiance for directional lights. */
		Degree mSpotAngle; /**< Total angle covered by a spot light. */
		Degree mSpotFalloffAngle; /**< Spot light angle at which falloff starts. Must be smaller than total angle. */
		bool mIsActive; /**< Whether the light should be rendered or not. */
		Sphere mBounds; /**< Sphere that bounds the light area of influence. */
	};

	/**
	 * Core thread usable version of a light.
	 *
	 * @see		LightBase
	 */
	class BS_EXPORT LightCore : public CoreObjectCore, public LightBase
	{
	public:
		~LightCore();

		/**	Sets an ID that can be used for uniquely identifying this object by the renderer. */
		void setRendererId(UINT32 id) { mRendererId = id; }

		/**	Retrieves an ID that can be used for uniquely identifying this object by the renderer. */
		UINT32 getRendererId() const { return mRendererId; }

		/**	Returns a mesh that represents the light's bounds. */
		SPtr<MeshCore> getMesh() const;

		static const UINT32 LIGHT_CONE_NUM_SIDES;
		static const UINT32 LIGHT_CONE_NUM_SLICES;
	protected:
		friend class Light;

		LightCore(LightType type, Color color, float intensity, 
			float range, bool castsShadows, Degree spotAngle, Degree spotFalloffAngle);

		/** @copydoc CoreObjectCore::initialize */
		void initialize() override;

		/** @copydoc CoreObject::syncToCore */
		void syncToCore(const CoreSyncData& data) override;

		UINT32 mRendererId;
		SPtr<MeshCore> mMesh;
	};

	/**
	 * Sim thread usable version of a light.
	 *
	 * @see		LightBase
	 */
	class BS_EXPORT Light : public IReflectable, public CoreObject, public LightBase
	{
	public:
		/**	Retrieves an implementation of a light usable only from the core thread. */
		SPtr<LightCore> getCore() const;

		/** Returns the hash value that can be used to identify if the internal data needs an update. */
		UINT32 _getLastModifiedHash() const { return mLastUpdateHash; }

		/**	Sets the hash value that can be used to identify if the internal data needs an update. */
		void _setLastModifiedHash(UINT32 hash) { mLastUpdateHash = hash; }

		/**
		 * Updates internal transform values from the specified scene object, in case that scene object's transform changed
		 * since the last call.
		 *
		 * @note	Assumes the same scene object will be provided every time.
		 */
		void _updateTransform(const HSceneObject& parent);

		/**
		 * Creates a new light with provided settings.
		 *
		 * @param[in]	type				Type of light that determines how are the rest of the parameters interpreted.
		 * @param[in]	color				Color of the light.
		 * @param[in]	intensity			Power of the light source. This will be luminous flux for point & spot lights, 
		 *									and radiance for directional lights.
		 * @param[in]	range				Cut off range for the light when rendering.
		 * @param[in]	castsShadows		Determines whether the light casts shadows.
		 * @param[in]	spotAngle			Total angle covered by a spot light.
		 * @param[in]	spotFalloffAngle	Spot light angle at which falloff starts. Must be smaller than total angle.
		 */
		static SPtr<Light> create(LightType type = LightType::Point, Color color = Color::White,
			float intensity = 100.0f, float range = 10.0f, bool castsShadows = false,
			Degree spotAngle = Degree(45), Degree spotFalloffAngle = Degree(40));

	protected:
		Light(LightType type, Color color, float intensity, float range, 
			bool castsShadows, Degree spotAngle, Degree spotFalloffAngle);

		/** @copydoc CoreObject::createCore */
		SPtr<CoreObjectCore> createCore() const override;

		/** @copydoc CoreObject::markCoreDirty */
		void _markCoreDirty(LightDirtyFlag flag = LightDirtyFlag::Everything) override;

		/** @copydoc CoreObject::syncToCore */
		CoreSyncData syncToCore(FrameAlloc* allocator) override;

		/**	Creates a light with without initializing it. Used for serialization. */
		static SPtr<Light> createEmpty();

		UINT32 mLastUpdateHash;

		/************************************************************************/
		/* 								RTTI		                     		*/
		/************************************************************************/
	public:
		friend class LightRTTI;
		static RTTITypeBase* getRTTIStatic();
		virtual RTTITypeBase* getRTTI() const override;

	protected:
		Light(); // Serialization only
	};
}