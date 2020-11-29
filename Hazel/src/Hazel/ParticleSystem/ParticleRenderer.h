#pragma once

#include "Hazel/Rendering/Renderer2D.h"
#include "Hazel/Rendering/SquareMesh.h"
#include "Particle.h"

namespace Hazel
{
	class ParticleRenderer
	{
	private:
		DrawData drawData;

	public:
		ParticleRenderer()
			: drawData({SquareMesh::CreateMesh()})
		{
		}

		void RenderParticle(Renderer2D &renderer, const Particle &particle)
		{
			if (particle.Active)
			{
				drawData.Mesh->SetColor(particle.GetColor());
				drawData.Transform = particle.Transform;
				renderer.Render(drawData);
			}
		}
	};
}