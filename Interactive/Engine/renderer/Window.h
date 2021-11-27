#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TurtleEngine
{
	class Window
	{
	public:
		static bool IsClosed() { return glfwWindowShouldClose(GlWindow); }

		static int GetWidth() { return Width; }
		static int GetHeight() { return Height; }
		static GLFWwindow* GetGlfwWindow() { return GlWindow; }

	private:
		friend struct GLFWwindow;
		friend class Engine;

		static GLint Width;
		static GLint Height;
		static GLFWwindow* GlWindow;

		static bool InitializeWindow(int width, int height);
		static void Update();
		static void Clear();
		static void DestroyWindow();

		friend static void WindowResizeCallback(GLFWwindow* window, GLint width, GLint height);
	};
}
