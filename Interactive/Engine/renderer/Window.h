#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Interactive.h"

class Interactive;
namespace IE
{

	class Window
	{
	public:
		Window(const char* windowName, int width, int height);
		~Window();

		void Update() const;
		static void Clear();
		bool IsClosed() const { return glfwWindowShouldClose(GlWindow); }

		int GetWidth() const { return Width; }
		int GetHeight() const { return Height; }
		GLFWwindow* GetGlfwWindow() const { return GlWindow; }

	private:
		friend struct GLFWwindow;
		friend class Interactive;

		GLint Width;
		GLint Height;
		const char* WindowName;
		GLFWwindow* GlWindow;

		bool InitializeWindow();
		friend static void WindowResizeCallback(GLFWwindow* window, GLint width, GLint height);
	};
}
