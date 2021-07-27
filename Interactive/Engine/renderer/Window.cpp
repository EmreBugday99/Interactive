#include "Window.h"
#include <iostream>
#include "../Interactive.h"
#include "../components/Camera.h"

Window::Window(std::string windowName, int width, int height, Interactive* engine)
	: Engine(engine), Width(width), Height(height), WindowName(windowName), GlWindow(nullptr)
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
	Interactive* engine = static_cast<Interactive*>(glfwGetWindowUserPointer(window));

	engine->GameWindow->Width = width;
	engine->GameWindow->Height = height;

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

	GlWindow = glfwCreateWindow(Width, Height, WindowName.c_str(), 0, 0);
	if (GlWindow == nullptr)
		return false;

	glfwMakeContextCurrent(GlWindow);
	glfwSetWindowUserPointer(GlWindow, Engine);
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}