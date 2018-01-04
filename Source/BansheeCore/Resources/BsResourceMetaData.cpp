//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Resources/BsResourceMetaData.h"
#include "RTTI/BsResourceMetaDataRTTI.h"

namespace bs
{
	RTTITypeBase* ResourceMetaData::getRTTIStatic()
	{
		return ResourceMetaDataRTTI::instance();
	}

	RTTITypeBase* ResourceMetaData::getRTTI() const
	{
		return ResourceMetaData::getRTTIStatic();
	}
}