//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Components/BsCAudioSource.h"
#include "Scene/BsSceneObject.h"
#include "Utility/BsTime.h"
#include "RTTI/BsCAudioSourceRTTI.h"

using namespace std::placeholders;

namespace bs
{
	CAudioSource::CAudioSource(const HSceneObject& parent)
		: Component(parent), mVolume(1.0f), mPitch(1.0f), mLoop(false), mPriority(0), mMinDistance(1.0f), mAttenuation(1.0f)
		, mPlayOnStart(true)
	{
		setName("AudioSource");

		mNotifyFlags = TCF_Transform;
	}

	void CAudioSource::setClip(const HAudioClip& clip)
	{
		if (mAudioClip == clip)
			return;

		mAudioClip = clip;

		if (mInternal != nullptr)
			mInternal->setClip(clip);
	}

	void CAudioSource::setVolume(float volume)
	{
		if (mVolume == volume)
			return;

		mVolume = volume;

		if (mInternal != nullptr)
			mInternal->setVolume(volume);
	}

	void CAudioSource::setPitch(float pitch)
	{
		if (mPitch == pitch)
			return;

		mPitch = pitch;

		if (mInternal != nullptr)
			mInternal->setPitch(pitch);
	}

	void CAudioSource::setIsLooping(bool loop)
	{
		if (mLoop == loop)
			return;

		mLoop = loop;

		if (mInternal != nullptr)
			mInternal->setIsLooping(loop);
	}

	void CAudioSource::setPriority(UINT32 priority)
	{
		if (mPriority == priority)
			return;

		mPriority = priority;

		if (mInternal != nullptr)
			mInternal->setPriority(priority);
	}

	void CAudioSource::setMinDistance(float distance)
	{
		if (mMinDistance == distance)
			return;

		mMinDistance = distance;

		if (mInternal != nullptr)
			mInternal->setMinDistance(distance);
	}

	void CAudioSource::setAttenuation(float attenuation)
	{
		if (mAttenuation == attenuation)
			return;

		mAttenuation = attenuation;

		if (mInternal != nullptr)
			mInternal->setAttenuation(attenuation);
	}

	void CAudioSource::play()
	{
		if (mInternal != nullptr)
			mInternal->play();
	}

	void CAudioSource::pause()
	{
		if (mInternal != nullptr)
			mInternal->pause();
	}

	void CAudioSource::stop()
	{
		if (mInternal != nullptr)
			mInternal->stop();
	}

	void CAudioSource::setTime(float position)
	{
		if (mInternal != nullptr)
			mInternal->setTime(position);
	}

	float CAudioSource::getTime() const
	{
		if (mInternal != nullptr)
			return mInternal->getTime();

		return 0.0f;
	}

	AudioSourceState CAudioSource::getState() const
	{
		if (mInternal != nullptr)
			return mInternal->getState();

		return AudioSourceState::Stopped;
	}

	void CAudioSource::onInitialized()
	{

	}

	void CAudioSource::onDestroyed()
	{
		destroyInternal();
	}

	void CAudioSource::onDisabled()
	{
		destroyInternal();
	}

	void CAudioSource::onEnabled()
	{
		restoreInternal();

		if (mPlayOnStart)
			play();
	}

	void CAudioSource::onTransformChanged(TransformChangedFlags flags)
	{
		if (!SO()->getActive())
			return;

		if ((flags & (TCF_Parent | TCF_Transform)) != 0)
			updateTransform();
	}

	void CAudioSource::update()
	{
		Vector3 worldPos = SO()->getTransform().getPosition();
		mVelocity = (worldPos - mLastPosition) / gTime().getFrameDelta();
		mLastPosition = worldPos;
	}

	void CAudioSource::restoreInternal()
	{
		if (mInternal == nullptr)
			mInternal = AudioSource::create();

		// Note: Merge into one call to avoid many virtual function calls
		mInternal->setClip(mAudioClip);
		mInternal->setVolume(mVolume);
		mInternal->setPitch(mPitch);
		mInternal->setIsLooping(mLoop);
		mInternal->setPriority(mPriority);
		mInternal->setMinDistance(mMinDistance);
		mInternal->setAttenuation(mAttenuation);

		updateTransform();
	}

	void CAudioSource::destroyInternal()
	{
		// This should release the last reference and destroy the internal listener
		mInternal = nullptr;
	}

	void CAudioSource::updateTransform()
	{
		mInternal->setTransform(SO()->getTransform());
		mInternal->setVelocity(mVelocity);
	}

	RTTITypeBase* CAudioSource::getRTTIStatic()
	{
		return CAudioSourceRTTI::instance();
	}

	RTTITypeBase* CAudioSource::getRTTI() const
	{
		return CAudioSource::getRTTIStatic();
	}
}