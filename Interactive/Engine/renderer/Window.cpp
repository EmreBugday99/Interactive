#include "Window.h"
#include <iostream>

Window::Window(std::string windowName, int width, int height)
{
	GlWindow = nullptr;
	WindowName = windowName;
	Width = width;
	Height = height;

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
	Window* gameWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	gameWindow->Width = width;
	gameWindow->Height = height;

	glViewport(0, 0, width, height);
}

bool Window::InitializeWindow()
{
	if (glfwInit() == 0)
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GlWindow = glfwCreateWindow(Width, Height, WindowName.c_str(), 0, 0);
	if (GlWindow == nullptr)
		return false;

	glfwMakeContextCurrent(GlWindow);
	glfwSetWindowUserPointer(GlWindow, this);
	glfwSetWindowSizeCallback(GlWindow, WindowResizeCallback);
	gladLoadGL();

	return true;
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(GlWindow);
}

void Window::Clear()
{
	glClearColor(0.1f, 0.16f, 0.12f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}