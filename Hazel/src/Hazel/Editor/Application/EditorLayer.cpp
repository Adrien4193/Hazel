#include "EditorLayer.h"

#include "imgui.h"

#include "Hazel/Core/Logging/Log.h"
#include "Hazel/Rendering/Textures/TextureFactory.h"
#include "Hazel/Tests/TestCameraController.h"
#include "Hazel/Tests/TestParticles.h"
#include "EditorViewport.h"
#include "Hazel/Scene/Serialization/SceneSerializer.h"
#include "Hazel/Scene/Parsing/SceneParser.h"
#include "Hazel/Core/FileSystem/FileDialog.h"

namespace Hazel
{
	EditorLayer::EditorLayer()
		: Layer("Hazel Editor")
	{
	}

	void EditorLayer::OnAttach()
	{
		auto &graphicsContext = GetGraphicsContext();

		rendererInfo.MaxIndexCount = 60000;
		rendererInfo.MaxVertexCount = 40000;
		rendererInfo.MaxTextureSlotCount = graphicsContext.GetMaxTextureSlotCount();
		renderer = std::make_shared<Renderer2D>(graphicsContext, rendererInfo);

		framebuffer = graphicsContext.CreateFramebuffer({{GetWindow().GetSize()}});

		spriteSheet = TextureFactory::CreateTextureFromFile(
			GetGraphicsContext(),
			"assets\\textures\\SpriteSheet.png");
		region = spriteSheet.GetRegion();

		scene = std::make_shared<Scene>("Test");
		scene->Attach(*this);
		scene->SetRenderer(*renderer);

		auto square1 = scene->CreateEntity();
		square1.AddComponent<TagComponent>("Square1");
		square1.AddComponent<SpriteComponent>(glm::vec4(1.0f), spriteSheet);
		square1.AddComponent<TransformComponent>().Transform.Scale.x = spriteSheet.GetRegion().GetAspectRatio();

		auto square2 = scene->CreateEntity();
		square2.AddComponent<TagComponent>("Square2");
		square2.AddComponent<SpriteComponent>(glm::vec4(1.0f));
		square2.AddComponent<TransformComponent>();

		camera1 = scene->CreateEntity();
		camera1.AddComponent<TagComponent>("Camera1");
		camera1.AddComponent<TransformComponent>();
		camera1.AddComponent<NativeScriptComponent>(std::make_shared<TestCameraController>());
		camera1.AddComponent<CameraComponent>();

		scene->SetPrimaryCamera(camera1);

		camera2 = scene->CreateEntity();
		camera2.AddComponent<TagComponent>("Camera2");
		camera2.AddComponent<TransformComponent>().Transform.Translation.x = 1.0f;
		camera2.AddComponent<CameraComponent>();

		auto particleEmitter = scene->CreateEntity();
		particleEmitter.AddComponent<TagComponent>("Particle Emitter");
		particleEmitter.AddComponent<TransformComponent>().Transform.Translation.z += 0.1f;
		particleEmitter.AddComponent<ParticleComponent>();
		particleEmitter.AddComponent<NativeScriptComponent>(std::make_shared<TestParticles>());
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate()
	{
		if (viewport.IsEmpty())
		{
			return;
		}

		scene->OnUpdate();

		GetGraphicsContext().SetFramebuffer(framebuffer.get());
		GetGraphicsContext().Clear();
		scene->OnRender();
		GetGraphicsContext().SetFramebuffer(nullptr);
	}

	void EditorLayer::OnGui()
	{
		editorWindow.Begin("Hazel");

		menu.Draw();
		if (menu.WantQuit())
		{
			CloseApplication();
		}
		if (menu.WantOpen())
		{
			FileDialog dialog(GetWindow());
			dialog.AddFilter({"YAML files", "*.yaml"});
			auto filename = dialog.GetOpenFilename();
			if (!filename.empty())
			{
				SceneParser::ParseFile(filename, *scene);
			}
		}
		if (menu.WantSave())
		{
			FileDialog dialog(GetWindow());
			dialog.AddFilter({"YAML files", "*.yaml"});
			auto filename = dialog.GetSaveFilename();
			if (!filename.empty())
			{
				SceneSerializer::Serialize(filename, *scene);
			}
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
		ImGui::Begin("Viewport");

		EnableGuiKeyboardFilter(!ImGui::IsWindowFocused());
		EnableGuiMouseFilter(!ImGui::IsWindowHovered());

		auto newViewport = EditorViewport::GetViewport(GetWindow());
		auto viewportSize = newViewport.GetSize();
		if (newViewport != viewport)
		{
			viewport = newViewport;

			Log::Warn("New viewport size: {} {}", viewportSize.x, viewportSize.y);
			if (!viewport.IsEmpty())
			{
				framebuffer = GetGraphicsContext().CreateFramebuffer({viewportSize});
			}
			scene->OnViewportResize(newViewport);
			OnUpdate();
		}

		ImGui::Image(
			framebuffer->GetColorAttachment()->GetHandle(),
			{viewportSize.x, viewportSize.y},
			{0.0f, 1.0f},
			{1.0f, 0.0f});

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::Begin("Test");
		if (ImGui::Checkbox("Camera 1", &useCamera1))
		{
			scene->SetPrimaryCamera(useCamera1 ? camera1 : camera2);
		}
		ImGui::End();

		ImGui::Begin("Settings");
		fpsPanel.Draw(GetDeltaTime());
		rendererStatisticsPanel.Draw(renderer->GetStatistics());
		if (batchPanel.Draw(rendererInfo))
		{
			renderer = std::make_shared<Renderer2D>(GetGraphicsContext(), rendererInfo);
			scene->SetRenderer(*renderer);
		}
		ImGui::End();

		scenePanel.Draw("Scene Hierarchy", *scene);

		editorWindow.End();
	}

	void EditorLayer::OnEvent(Event &e)
	{
		scene->OnEvent(e);
	}
}