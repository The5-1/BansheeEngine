//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "RenderAPI/BsEventQuery.h"
#include "Managers/BsQueryManager.h"

namespace bs { namespace ct
{
	SPtr<EventQuery> EventQuery::create(UINT32 deviceIdx)
	{
		return QueryManager::instance().createEventQuery(deviceIdx);
	}
}}