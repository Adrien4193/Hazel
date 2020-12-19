#pragma once

#include "Hazel/Core/Application/Layer.h"
#include "Hazel/Rendering/Renderer2D/Renderer2D.h"

namespace Hazel
{
	struct SceneInfo
	{
		Layer *Layer = nullptr;
		Renderer2D *Renderer = nullptr;
	};
}