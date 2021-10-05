#include "Window.h"
#include <iostream>
#include <glm/vec4.hpp>
#include "../Interactive.h"

namespace IE
{
	Window::Window(const char* windowName, int width, int height)
		: Width(width), Height(height), WindowName(windowName), GlWindow(nullptr)
	{
		if (InitializeWindow() == false)
		{
			std::cerr << "[ERROR] Failed to initialize window!" << std::endl;
			glfwTerminate();
			return;
		}

		std::cout << "[OPEN GL] Version: " << glGetString(GL_VERSION) << std::endl;
	}

	Window::~Window()
	{
		glfwDestroyWindow(GlWindow);
	}

	void WindowResizeCallback(GLFWwindow* window, GLint width, GLint height)
	{
		Interactive::GameWindow.Width = width;
		Interactive::GameWindow.Height = height;

		glViewport(0, 0, width, height);

		engine->MainCamera->SetProjection(glm::vec4(0.0f, width, 0.0f, height));
	}



	bool Window::InitializeWindow()
	{
		if (glfwInit() == 0)
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GlWindow = glfwCreateWindow(Width, Height, WindowName, nullptr, nullptr);
		if (GlWindow == nullptr)
			return false;

		glfwMakeContextCurrent(GlWindow);
		glfwSetWindowSizeCallback(GlWindow, WindowResizeCallback);
		gladLoadGL();

		return true;
	}

	void Window::Update() const
	{
		glfwPollEvents();
		glfwSwapBuffers(GlWindow);
	}

	void Window::Clear()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}