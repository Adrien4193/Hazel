#pragma once

#include <memory>

#include "Logger.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Hazel/Events/Events.h"
#include "Hazel/Utils/Reversed.h"

namespace Hazel
{
    class ApplicationImplementation : public EventListener
    {
    private:
        std::unique_ptr<Window> window;
        ImGuiLayer *imguiLayer;
        bool running = false;
        LayerStack layers;

    public:
        ApplicationImplementation()
            : window(Window::Create()),
            imguiLayer(new Hazel::ImGuiLayer(*window.get()))
        {
            Init();
        }

        inline const Window &GetWindow()
        {
            return *window.get();
        }

        inline void Run()
        {
            CoreInfo("Application started.");
            running = true;
            while (running)
            {
                Update();
            }
            CoreInfo("Application stopped.");
        }

        inline void Quit()
        {
            running = false;
        }

        inline void PushLayer(Layer *layer)
        {
            layers.PushLayer(layer);
        }

        inline void PushOverlay(Layer *overlay)
        {
            layers.PushOverlay(overlay);
        }

        virtual void OnEvent(Event &e) override
        {
            CoreDebug("{}", e);
            for (Layer *layer : layers)
            {
                EventDispatcher(layer).Dispatch(e);
            }
        }

        virtual void OnWindowClosed(WindowClosedEvent &e) override
        {
            Quit();
        }

    private:
        inline void Init()
        {
            CoreDebug("Application initialization.");
            SetupWindow();
            PushOverlay(imguiLayer);
            CoreDebug("Application initialized.");
        }

        inline void SetupWindow()
        {
            CoreDebug("Main window setup started.");
            window->SetEventListener(this);
            CoreDebug("Main window setup done.");
        }

        inline void Update()
        {
            UpdateLayers();
            RenderImGui();
            window->OnUpdate();
        }

        inline void UpdateLayers()
        {
            CoreTrace("Update Layers");
            for (Layer *layer : Reversed(layers))
            {
                layer->OnUpdate();
            }
        }

        inline void RenderImGui()
        {
            CoreTrace("Render ImGui");
            imguiLayer->Begin();
            for (Layer *layer : Reversed(layers))
            {
                layer->OnImGuiRender();
            }
            imguiLayer->End();
        }
    };
}