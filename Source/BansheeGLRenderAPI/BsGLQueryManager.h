//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsGLPrerequisites.h"
#include "Managers/BsQueryManager.h"

namespace bs { namespace ct
{
	/** @addtogroup GL
	 *  @{
	 */

	/**	Handles creation and life of OpenGL queries. */
	class GLQueryManager : public QueryManager
	{
	public:
		/** @copydoc QueryManager::createEventQuery */
		SPtr<EventQuery> createEventQuery(UINT32 deviceIdx = 0) const override;

		/** @copydoc QueryManager::createTimerQuery */
		SPtr<TimerQuery> createTimerQuery(UINT32 deviceIdx = 0) const override;

		/** @copydoc QueryManager::createOcclusionQuery */
		SPtr<OcclusionQuery> createOcclusionQuery(bool binary, UINT32 deviceIdx = 0) const override;
	};

	/** @} */
}}