#pragma once

#include "Hazel.h"
#include "TestParticle.h"

namespace Sandbox
{
	class SandboxLayer : public Hazel::Layer
	{
	private:
		float renderTime = 0.0f;
		int maxVertices = 40000;
		int maxIndices = 60000;
		glm::vec2 bottomLeft{0.0f};
		glm::vec2 size{2560.0f, 1664.0f};

		std::shared_ptr<Hazel::Renderer2D> renderer;
		Hazel::OrthographicCamera camera;
		Hazel::OrthographicCameraController cameraController;
		Hazel::DrawData drawData;
		std::shared_ptr<Hazel::Texture> spriteSheet;
		TestParticle particles;

	public:
		SandboxLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Hazel::Event &e) override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnImGuiRender() override;
	};
}