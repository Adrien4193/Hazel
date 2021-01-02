#include "Renderer2D.h"

#include "Hazel/Rendering/Textures/TextureFactory.h"

namespace Hazel
{
	Renderer2D::Renderer2D(GraphicsContext &graphicsContext, const RendererInfo &info)
		: batchRenderer(graphicsContext, info)
	{
	}

	void Renderer2D::BeginScene(const glm::mat4 &viewProjection)
	{
		batchRenderer.BeginScene(viewProjection);
	}

	void Renderer2D::Render(const DrawData &drawData)
	{
		batchRenderer.Render(drawData);
	}

	void Renderer2D::EndScene()
	{
		batchRenderer.EndScene();
	}
}