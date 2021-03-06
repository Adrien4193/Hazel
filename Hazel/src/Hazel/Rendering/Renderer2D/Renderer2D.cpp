#include "Renderer2D.h"

#include "SquareMesh.h"
#include "Shader2D.h"

namespace Hazel
{
	Renderer2D::Renderer2D(const RendererInfo &info)
		: renderer(info),
		squareMesh(SquareMesh::CreateMesh()),
		defaultShader(Shader2D::CreateShader(*info.GraphicsContext))
	{
	}

	void Renderer2D::BeginScene(const Camera &camera, const std::shared_ptr<Framebuffer> &framebuffer)
	{
		renderer.BeginScene(camera, framebuffer);
	}

	void Renderer2D::EndScene()
	{
		renderer.EndScene();
	}
}