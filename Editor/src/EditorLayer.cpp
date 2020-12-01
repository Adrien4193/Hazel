#include "EditorLayer.h"

#include "imgui.h"

#include "Hazel/Textures/TextureBuilder.h"
#include "Hazel/Rendering/SquareMesh.h"
#include "Hazel/Logging/Log.h"

namespace Hazel
{
	EditorLayer::EditorLayer()
		: Layer("Hazel Editor")
	{
	}

	void EditorLayer::OnAttach()
	{
		auto &graphicsContext = GetGraphicsContext();

		BatchInfo rendererInfo;
		rendererInfo.MaxIndexCount = maxIndices;
		rendererInfo.MaxVertexCount = maxVertices;
		rendererInfo.MaxTextureSlotCount = graphicsContext.GetMaxTextureSlotCount();
		renderer = std::make_shared<Renderer2D>(graphicsContext, rendererInfo);

		framebuffer = graphicsContext.CreateFramebuffer({GetWindow().GetSize()});

		squareMesh = SquareMesh::CreateMesh();

		spriteSheet = TextureBuilder::CreateTextureFromFile(
			GetGraphicsContext(),
			"assets\\textures\\SpriteSheet.png");

		cameraController.OnAttach(camera, GetWindow().GetSize());

		square = scene.CreateEntity();
		square.AddComponent<SpriteComponent>();
		square.AddComponent<TransformComponent>().Transform.Scale.x = spriteSheet.GetAspectRatio();
		square.AddComponent<TextureComponent>(spriteSheet);

		cameraEntity = scene.CreateEntity();
		cameraEntity.AddComponent<TransformComponent>();
		cameraEntity.AddComponent<CameraComponent>().SetWindowSize(GetWindow().GetSize());
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(float deltaTime)
	{
		renderTime = deltaTime;

		cameraController.OnUpdate(camera, GetInput(), deltaTime);

		SubTexture &texture = square.GetComponent<TextureComponent>();
		texture.SetRegion(Rectangle::FromBottomLeftAndSize(bottomLeft, size));

		GetGraphicsContext().SetFramebuffer(framebuffer.get());
		GetGraphicsContext().Clear();
		sceneRenderer.Render(scene, *renderer);
		GetGraphicsContext().SetFramebuffer(nullptr);
	}

	void EditorLayer::OnImGuiRender()
	{
		dockspace.Begin();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
		ImGui::Begin("Viewport");

		bool blockKeyboard = !ImGui::IsWindowFocused();
		bool blockMouse = !ImGui::IsWindowHovered();
		EnableImGuiKeyboardFilter(blockKeyboard);
		EnableImGuiMouseFilter(blockMouse);
		if (!this->blockKeyboard && blockKeyboard)
		{
			GetInput().ClearKeys();
		}
		if (!this->blockMouse && blockMouse)
		{
			GetInput().ClearMouseButtons();
		}
		this->blockKeyboard = blockKeyboard;
		this->blockMouse = blockMouse;

		auto viewportSize = ImGui::GetContentRegionAvail();
		glm::vec2 newSize = {viewportSize.x, viewportSize.y};
		if (newSize != framebuffer->GetSize())
		{
			Log::Debug("New viewport size: {} {}", newSize.x, newSize.y);
			framebuffer = GetGraphicsContext().CreateFramebuffer({newSize});
			//cameraController.OnEvent(camera, e);
			cameraEntity.GetComponent<CameraComponent>().SetWindowSize(newSize);
		}

		ImGui::Image(
			framebuffer->GetColorAttachment()->GetHandle(),
			viewportSize,
			{0.0f, 1.0f},
			{1.0f, 0.0f});

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::Begin("Info");
		ImGui::Text("Update Time: %fms (%fFPS)", 1000 * renderTime, 1.0f / renderTime);
		ImGui::Text("Camera Position: %f %f %f", camera.GetPosition().x, camera.GetPosition().y, camera.GetZoomLevel());
		ImGui::Text("Camera Rotation: %fdeg", glm::degrees(camera.GetRotation()));
		ImGui::End();

		Transform &transform = square.GetComponent<TransformComponent>();
		ImGui::Begin("Transform");
		ImGui::SliderFloat2("Translation", glm::value_ptr(transform.Position), -10.0f, 10.0f);
		ImGui::SliderFloat("Rotation", &transform.Angle, 0.0f, glm::radians(360.0f));
		ImGui::SliderFloat2("Scale", glm::value_ptr(transform.Scale), 0.0f, glm::radians(360.0f));
		ImGui::End();

		ImGui::Begin("Texture Coordinates");
		ImGui::SliderFloat("Left", &bottomLeft.x, 0.0f, 2560.0f);
		ImGui::SliderFloat("Bottom", &bottomLeft.y, 0.0f, 1664.0f);
		ImGui::SliderFloat("Width", &size.x, 0.0f, 2560.0f);
		ImGui::SliderFloat("Height", &size.y, 0.0f, 1664.0f);
		ImGui::End();

		ImGui::Begin("Renderer");
		ImGui::SliderInt("MaxVertices", &maxVertices, 0, 100000);
		ImGui::SliderInt("MaxIndices", &maxIndices, 0, 100000);
		ImGui::Text("DrawCall: %zu", renderer->GetStatistics().DrawCallCount);
		ImGui::Text("VertexCount: %zu", renderer->GetStatistics().VertexCount);
		ImGui::Text("IndexCount: %zu", renderer->GetStatistics().IndexCount);
		ImGui::Text("TextureCount: %zu", renderer->GetStatistics().TextureCount);
		if (ImGui::Button("Reset"))
		{
			OnAttach();
		}
		ImGui::End();

		dockspace.End();
	}

	void EditorLayer::OnEvent(Event &e)
	{
		cameraController.OnEvent(camera, e);
		renderer->OnEvent(e);
		e.Dispatch([this](KeyPressEvent &e)
		{
			if (e.GetKey() == Key::Backspace)
			{
				camera = {};
				cameraController.OnAttach(camera, framebuffer->GetSize());
			}
		});
	}
}