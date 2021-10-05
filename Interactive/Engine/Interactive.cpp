#include "Interactive.h"
#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_glfw.h"
#include "external/imgui/imgui_impl_opengl3.h"
#include "ecs/SystemManager.hpp"
#include <GLFW/glfw3.h>
#include "renderer/texture/TextureManager.h"

namespace IE
{
	const char* Interactive::GameName;
	Window Interactive::GameWindow;
	InputManager Interactive::InputSystem;
	TextureManager Interactive::TextureSystem;

	void Interactive::Initialize(const char* gameName)
	{
		GameWindow = Window(gameName, 800, 800);
		InputSystem = InputManager();
		TextureSystem = TextureManager();

		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(GameWindow.GlWindow, true);
		ImGui_ImplOpenGL3_Init("#version 150");
		ImGui::StyleColorsDark();
	}

	void Interactive::Start()
	{
		Update();
	}

	void Interactive::Update()
	{
		while (GameWindow.IsClosed() == false)
		{
			GameWindow.Clear();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			for (const auto renderCallback : SystemManager::RenderCallbacks)
			{
				renderCallback();
			}

			InputSystem.ClearKeyStates();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			GameWindow.Update();
		}

		Close();
	}

	void Interactive::Close()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwTerminate();
	}
}