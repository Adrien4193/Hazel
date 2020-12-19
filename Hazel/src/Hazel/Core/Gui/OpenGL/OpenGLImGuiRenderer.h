#pragma once

#include "Hazel/Core/Gui/GuiRenderer.h"

struct GLFWwindow;

namespace Hazel
{
	class OpenGLImGuiRenderer : public GuiRenderer
	{
	public:
		OpenGLImGuiRenderer(GLFWwindow *window);
		virtual ~OpenGLImGuiRenderer();

		virtual void CreateNewFrame() override;
		virtual void RenderDrawData() override;
	};
}