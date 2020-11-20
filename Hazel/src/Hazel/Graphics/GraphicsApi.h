#pragma once

#include "Hazel/Graphics/GraphicsContext.h"

namespace Hazel
{
	class GraphicsApi
	{
	public:
		virtual ~GraphicsApi() = default;

		virtual std::shared_ptr<GraphicsContext> CreateContext(GLFWwindow *window) = 0;
	};
}