//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Audio/BsAudioClipImportOptions.h"
#include "RTTI/BsAudioClipImportOptionsRTTI.h"

namespace bs
{
	AudioClipImportOptions::AudioClipImportOptions()
		:mFormat(AudioFormat::PCM), mReadMode(AudioReadMode::LoadDecompressed), mIs3D(true), mBitDepth(16)
	{
		
	}

	SPtr<AudioClipImportOptions> AudioClipImportOptions::create()
	{
		return bs_shared_ptr_new<AudioClipImportOptions>();
	}

	/************************************************************************/
	/* 								SERIALIZATION                      		*/
	/************************************************************************/
	RTTITypeBase* AudioClipImportOptions::getRTTIStatic()
	{
		return AudioClipImportOptionsRTTI::instance();
	}

	RTTITypeBase* AudioClipImportOptions::getRTTI() const
	{
		return getRTTIStatic();
	}
}