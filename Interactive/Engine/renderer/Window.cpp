#include "Window.h"
#include <iostream>

void WindowResizeCallback(GLFWwindow* window, GLint width, GLint height);

Window::Window(std::string windowName, int width, int height)
{
	m_Window = nullptr;
	m_Name = windowName;
	m_Width = width;
	m_Height = height;

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
	glfwDestroyWindow(m_Window);
}

bool Window::InitializeWindow()
{
	if (glfwInit() == 0)
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), NULL, NULL);
	if (m_Window == nullptr)
		return false;

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);
	gladLoadGL();

	return true;
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);

	// TODO: Performance heavy operation, implement an optimized way.
	glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
}

void Window::Clear()
{
	glClearColor(0.1f, 0.16f, 0.12f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void WindowResizeCallback(GLFWwindow* window, GLint width, GLint height)
{
	glViewport(0, 0, width, height);
}