#include "ApplicationSetup.h"

#include "ApplicationEvents.h"

namespace Hazel
{
	void ApplicationSetup::Setup(ApplicationContext &context)
	{
		Log::Debug("Application setup.");
		context.LoadGraphicsApi();
		context.CreateApplicationWindow();
		if (context.GetSettings().ImGuiEnabled)
		{
			context.GetLayers().PushImGuiLayer();
		}
		context.AttachLayers();
		context.SetEventCallback([&](Event &e)
		{
			ApplicationEvents::ProcessEvent(context, e);
		});
	}
}