//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsPrerequisites.h"
#include "RenderAPI/BsSubMesh.h"

namespace bs { namespace ct
{
	/** @addtogroup Renderer-Engine-Internal
	 *  @{
	 */

	/** Contains all information needed for rendering a single sub-mesh. Closely tied with Renderer. */
	class BS_EXPORT RenderableElement
	{
	public:
		/**	Reference to the mesh to render. */
		SPtr<Mesh> mesh;

		/**	Portion of the mesh to render. */
		SubMesh subMesh;

		/**	Material to render the mesh with. */
		SPtr<Material> material;
	};

	/** @} */
}}