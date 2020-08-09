#pragma once

#include "Mesh.h"
#include "Hazel/Geometry/Transform.h"
#include "Hazel/Rendering/Textures/SubTexture2D.h"

namespace Hazel
{
	struct DrawData
	{
		Mesh Mesh;
		Transform Transform;
		SubTexture2D Texture;
	};
}