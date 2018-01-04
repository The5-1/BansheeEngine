//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Audio/BsAudioSource.h"
#include "Audio/BsAudio.h"
#include "Math/BsMath.h"
#include "RTTI/BsAudioSourceRTTI.h"

namespace bs
{
	AudioSource::AudioSource()
		: mVelocity(BsZero), mVolume(1.0f), mPitch(1.0f), mLoop(false), mPriority(0), mMinDistance(1.0f), mAttenuation(1.0f)
	{

	}

	void AudioSource::setClip(const HAudioClip& clip)
	{
		mAudioClip = clip;

		markListenerResourcesDirty();
	}

	void AudioSource::setVelocity(const Vector3& velocity)
	{
		mVelocity = velocity;
	}

	void AudioSource::setVolume(float volume)
	{
		mVolume = Math::clamp01(volume);
	}

	void AudioSource::setPitch(float pitch)
	{
		mPitch = pitch;
	}

	void AudioSource::setIsLooping(bool loop)
	{
		mLoop = loop;
	}

	void AudioSource::setPriority(INT32 priority)
	{
		mPriority = priority;
	}

	void AudioSource::setMinDistance(float distance)
	{
		mMinDistance = distance;
	}

	void AudioSource::setAttenuation(float attenuation)
	{
		mAttenuation = attenuation;
	}

	SPtr<AudioSource> AudioSource::create()
	{
		return gAudio().createSource();
	}

	void AudioSource::getListenerResources(Vector<HResource>& resources)
	{
		if (mAudioClip != nullptr)
			resources.push_back(mAudioClip);
	}

	void AudioSource::notifyResourceChanged(const HResource& resource)
	{
		onClipChanged();
	}

	RTTITypeBase* AudioSource::getRTTIStatic()
	{
		return AudioSourceRTTI::instance();
	}

	RTTITypeBase* AudioSource::getRTTI() const
	{
		return AudioSource::getRTTIStatic();
	}
}