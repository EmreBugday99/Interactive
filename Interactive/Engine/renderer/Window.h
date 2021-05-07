#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class InteractiveEngine;

class Window
{
private:
	friend struct GLFWwindow;
	GLint Width;
	GLint Height;
	std::string WindowName;
	
	GLFWwindow* GlWindow;

public:
	Window(std::string windowName, int width, int height);
	~Window();

	void Update();
	void Clear();
	bool IsOpen() const { return glfwWindowShouldClose(GlWindow); }

	int GetWidth() const { return Width; }
	int GetHeight() const { return Height; }

private:
	bool InitializeWindow();
	friend static void WindowResizeCallback(GLFWwindow* window, GLint width, GLint height);
};
