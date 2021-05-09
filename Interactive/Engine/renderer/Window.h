#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class InteractiveEngine;
class Window
{
public:
	InteractiveEngine* Engine;

	~Window();

	void Update();
	void Clear();
	bool IsClosed() const { return glfwWindowShouldClose(GlWindow); }

	int GetWidth() const { return Width; }
	int GetHeight() const { return Height; }
	GLFWwindow* GetGlfwWindow() { return GlWindow; }

private:
	friend struct GLFWwindow;
	friend class InteractiveEngine;

	GLint Width;
	GLint Height;
	std::string WindowName;
	GLFWwindow* GlWindow;

	Window(std::string windowName, int width, int height, InteractiveEngine* engine);

	bool InitializeWindow();
	friend static void WindowResizeCallback(GLFWwindow* window, GLint width, GLint height);
};
