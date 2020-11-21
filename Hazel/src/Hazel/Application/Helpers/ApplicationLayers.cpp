#include "ApplicationLayers.h"

#include "Hazel/Utils/Reversed.h"

namespace Hazel
{
	ApplicationLayers::ApplicationLayers(LayersContext &context)
		: context(context)
	{
	}

	void ApplicationLayers::PushImGuiLayer()
	{
		imGuiLayer = std::make_shared<ImGuiLayer>();
		PushOverlay(imGuiLayer);
	}

	void ApplicationLayers::PushLayer(const std::shared_ptr<Layer> &layer)
	{
		layers.PushLayer(layer);
		layer->SetContext(context);
		layer->OnAttach();
	}

	void ApplicationLayers::PushOverlay(const std::shared_ptr<Layer> &overlay)
	{
		layers.PushOverlay(overlay);
		overlay->SetContext(context);
		overlay->OnAttach();
	}

	void ApplicationLayers::DispatchEvent(Event &e)
	{
		for (const auto &layer : layers)
		{
			if (e.IsHandled())
			{
				return;
			}
			layer->UpdateInput(e);
			layer->OnEvent(e);
		}
	}

	void ApplicationLayers::UpdateLayers(float deltaTime)
	{
		for (const auto &layer : Reversed(layers))
		{
			layer->OnUpdate(deltaTime);
		}
	}

	void ApplicationLayers::RenderImGui()
	{
		if (imGuiLayer)
		{
			imGuiLayer->BeginRender();
			for (const auto &layer : Reversed(layers))
			{
				layer->OnImGuiRender();
			}
			imGuiLayer->EndRender();
		}
	}
}