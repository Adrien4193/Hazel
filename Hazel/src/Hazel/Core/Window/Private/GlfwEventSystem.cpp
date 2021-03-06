#include "GlfwEventSystem.h"

#include "GLFW/glfw3.h"

#include "GlfwEventReceiver.h"

namespace Hazel
{
	GlfwEventReceiver &GlfwEventSystem::GetReceiver(GLFWwindow *window)
	{
		return *static_cast<GlfwEventReceiver *>(glfwGetWindowUserPointer(window));
	}

	void GlfwEventSystem::RemoveCallbacks(GLFWwindow *window)
	{
		glfwSetWindowSizeCallback(window, nullptr);
		glfwSetWindowCloseCallback(window, nullptr);
		glfwSetKeyCallback(window, nullptr);
		glfwSetCharCallback(window, nullptr);
		glfwSetMouseButtonCallback(window, nullptr);
		glfwSetScrollCallback(window, nullptr);
		glfwSetCursorPosCallback(window, nullptr);
	}

	void GlfwEventSystem::SetupCallbacks(GLFWwindow *window, GlfwEventReceiver &receiver)
	{
		glfwSetWindowUserPointer(window, &receiver);
		glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
		{
			GetReceiver(window).OnWindowResized(width, height);
		});
		glfwSetWindowCloseCallback(window, [](GLFWwindow *window)
		{
			GetReceiver(window).OnWindowClosed();
		});
		glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			GetReceiver(window).OnKey(key, scancode, action, mods);
		});
		glfwSetCharCallback(window, [](GLFWwindow *window, unsigned int key)
		{
			GetReceiver(window).OnChar(key);
		});
		glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods)
		{
			GetReceiver(window).OnMouseButton(button, action);
		});
		glfwSetScrollCallback(window, [](GLFWwindow *window, double x, double y)
		{
			GetReceiver(window).OnMouseScrolled(x, y);
		});
		glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y)
		{
			GetReceiver(window).OnMouseMoved(x, y);
		});
	}
}