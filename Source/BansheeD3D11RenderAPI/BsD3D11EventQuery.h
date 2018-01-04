//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsD3D11Prerequisites.h"
#include "RenderAPI/BsEventQuery.h"

namespace bs { namespace ct
{
	/** @addtogroup D3D11
	 *  @{
	 */

	/** @copydoc EventQuery */
	class D3D11EventQuery : public EventQuery
	{
	public:
		D3D11EventQuery(UINT32 deviceIdx);
		~D3D11EventQuery();

		/** @copydoc EventQuery::begin */
		void begin(const SPtr<CommandBuffer>& cb = nullptr) override;

		/** @copydoc EventQuery::isReady */
		bool isReady() const override;

	private:
		ID3D11Query* mQuery;
		ID3D11DeviceContext* mContext;
	};

	/** @} */
}}