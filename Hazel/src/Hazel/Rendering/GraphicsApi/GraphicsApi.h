#pragma once

#include "Hazel/Rendering/GraphicsContext/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel
{
	class GraphicsApi
	{
	public:
		virtual ~GraphicsApi() = default;

		virtual std::shared_ptr<GraphicsContext> CreateContext(GLFWwindow *window) = 0;
	};
}