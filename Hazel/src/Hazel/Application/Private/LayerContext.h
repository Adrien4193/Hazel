#pragma once

#include "ApplicationSettings.h"
#include "Hazel/Window/Window.h"
#include "Hazel/Events/EventSystem.h"

namespace Hazel
{
	class LayerContext
	{
	private:
		ApplicationSettings settings;
		std::unique_ptr<Window> window;
		EventSystem eventSystem;

	public:
		ApplicationSettings &GetSettings()
		{
			return settings;
		}

		const ApplicationSettings &GetSettings() const
		{
			return settings;
		}

		Window &CreateApplicationWindow(const WindowInfo &info)
		{
			window = std::make_unique<Window>(info);
			eventSystem.SetWindow(*window);
			return *window;
		}

		Window &GetWindow() const
		{
			return *window;
		}

		void SetEventCallback(const EventSystem::Callback &callback)
		{
			eventSystem.SetCallback(callback);
		}

		void SendEvent(Event &e)
		{
			eventSystem.SendEvent(e);
		}

		void PollEvents()
		{
			eventSystem.PollEvents();
		}
	};
}