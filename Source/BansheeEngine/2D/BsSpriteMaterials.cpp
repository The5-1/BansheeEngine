//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "2D/BsSpriteMaterials.h"
#include "Resources/BsBuiltinResources.h"
#include "RenderAPI/BsGpuBuffer.h"
#include "Material/BsMaterial.h"

namespace bs
{
	SpriteImageTransparentMaterial::SpriteImageTransparentMaterial()
		:SpriteMaterial(0, BuiltinResources::instance().createSpriteImageMaterial())
	{ }

	SpriteImageOpaqueMaterial::SpriteImageOpaqueMaterial()
		: SpriteMaterial(1, BuiltinResources::instance().createSpriteNonAlphaImageMaterial())
	{ }

	SpriteTextMaterial::SpriteTextMaterial()
		: SpriteMaterial(2, BuiltinResources::instance().createSpriteTextMaterial())
	{ }

	SpriteLineMaterial::SpriteLineMaterial()
		: SpriteMaterial(3, BuiltinResources::instance().createSpriteLineMaterial())
	{ }
}