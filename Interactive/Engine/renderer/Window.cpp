#include "Window.h"
#include <iostream>
#include "../Engine.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace TurtleEngine
{
	GLint Window::Width;
	GLint Window::Height;
	GLFWwindow* Window::GlWindow;

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(GlWindow);
	}

	void WindowResizeCallback(GLFWwindow* window, GLint width, GLint height)
	{
		Window::Width = width;
		Window::Height = height;

		glViewport(0, 0, width, height);

		//engine->MainCamera->SetProjection(glm::vec4(0.0f, width, 0.0f, height));
		Engine::ProjectionMatrix = glm::ortho(0.f, (float)width, 0.0f, (float)height);
	}

	bool Window::InitializeWindow(int width, int height)
	{
		std::cout << "aaa" << std::endl;

		if (glfwInit() == GLFW_FALSE)
			return false;

		std::cout << "bbb" << std::endl;

		Width = width;
		Height = height;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GlWindow = glfwCreateWindow(Width, Height, Engine::GetGameName(), nullptr, nullptr);
		if (GlWindow == nullptr)
		{
			std::cerr << "[ERROR] Failed to initialize window!" << std::endl;
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(GlWindow);
		glfwSetWindowSizeCallback(GlWindow, WindowResizeCallback);
		gladLoadGL();

		std::cout << "[OPEN GL] Version: " << glGetString(GL_VERSION) << std::endl;

		return true;
	}

	void Window::Clear()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::DestroyWindow()
	{
		glfwDestroyWindow(GlWindow);
	}
}