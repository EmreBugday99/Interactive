#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class InteractiveEngine;

class Window
{
private:
	GLint m_Width;
	GLint m_Height;
	std::string m_Name;

	GLFWwindow* m_Window;

public:
	Window(std::string windowName, int width, int height);
	~Window();

	void Update();
	void Clear();
	bool IsOpen() const { return glfwWindowShouldClose(m_Window); }

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

private:
	bool InitializeWindow();
};
