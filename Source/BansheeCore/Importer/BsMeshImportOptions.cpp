//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Importer/BsMeshImportOptions.h"
#include "RTTI/BsMeshImportOptionsRTTI.h"

namespace bs
{
	RTTITypeBase* AnimationSplitInfo::getRTTIStatic()
	{
		return AnimationSplitInfoRTTI::instance();
	}

	RTTITypeBase* AnimationSplitInfo::getRTTI() const
	{
		return AnimationSplitInfo::getRTTIStatic();
	}

	RTTITypeBase* ImportedAnimationEvents::getRTTIStatic()
	{
		return ImportedAnimationEventsRTTI::instance();
	}

	RTTITypeBase* ImportedAnimationEvents::getRTTI() const
	{
		return ImportedAnimationEvents::getRTTIStatic();
	}

	MeshImportOptions::MeshImportOptions()
		: mCPUCached(false), mImportNormals(true), mImportTangents(true), mImportBlendShapes(false), mImportSkin(false)
		, mImportAnimation(false), mReduceKeyFrames(true), mImportRootMotion(false), mImportScale(1.0f)
		, mCollisionMeshType(CollisionMeshType::None)
	{ }

	SPtr<MeshImportOptions> MeshImportOptions::create()
	{
		return bs_shared_ptr_new<MeshImportOptions>();
	}

	RTTITypeBase* MeshImportOptions::getRTTIStatic()
	{
		return MeshImportOptionsRTTI::instance();
	}

	RTTITypeBase* MeshImportOptions::getRTTI() const
	{
		return MeshImportOptions::getRTTIStatic();
	}
}