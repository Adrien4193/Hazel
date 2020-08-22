#include "ContextManager.h"

namespace Hazel
{
	ContextManager::ContextManager(const ContextInfo &info)
		: window(info),
		layerManager(window),
		context({
			layerManager,
			window.GetProperties(),
			window.GetInput(),
			info.RenderApi.GetFactory(),
			info.RenderApi.GetDrawer()})
	{
		window.GetEventManager().SetEventListener(this);
	}

	LayerManager &ContextManager::GetLayerManager()
	{
		return layerManager;
	}

	Context &ContextManager::GetContext()
	{
		return context;
	}

	bool ContextManager::HasWindowClosed() const
	{
		return windowClosed;
	}

	void ContextManager::OnUpdate()
	{
		context.Drawer.Clear();
		window.GetEventManager().PollEvents();
		layerManager.OnUpdate();
		window.GetContext().SwapBuffers();
	}

	void ContextManager::MakeCurrent()
	{
		window.GetContext().MakeCurrent();
		layerManager.OnContextCurrent();
	}

	void ContextManager::OnEvent(Event &e)
	{
		layerManager.OnEvent(e);
	}

	void ContextManager::OnWindowResized(WindowResizeEvent &e)
	{
		auto size = e.GetSize();
		context.Drawer.SetViewport({0.0f, size.Width, 0.0f, size.Height});
	}

	void ContextManager::OnWindowClosed(WindowCloseEvent &e)
	{
		windowClosed = true;
	}
}