#pragma once

#include "Hazel/Rendering/GraphicsApi/GraphicsApi.h"

namespace Hazel
{
	class OpenGL : public GraphicsApi
	{
	public:
		virtual std::shared_ptr<GraphicsContext> CreateContext(GLFWwindow *window) override;
	};
}