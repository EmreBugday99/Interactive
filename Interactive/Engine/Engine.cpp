#include "Engine.h"

#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_glfw.h"
#include "external/imgui/imgui_impl_opengl3.h"
#include "renderer/Window.h"
#include "World/World.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace TurtleEngine
{
	bool Engine::IsInitialized;
	const char* Engine::GameName;
	World* Engine::ActiveWorld;
	glm::mat4 Engine::ProjectionMatrix;

	void Engine::Initialize(const char* gameName, int width, int height)
	{
		if (IsInitialized)
			return;

		GameName = gameName;
		Window::InitializeWindow(width, height);

		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(Window::GetGlfwWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 150");
		ImGui::StyleColorsDark();

		ProjectionMatrix = glm::ortho(0.f, (float)width, 0.0f, (float)height);

		IsInitialized = true;
	}

	void Engine::Start()
	{
		Update();
	}


	void Engine::Update()
	{
		while (Window::IsClosed() == false)
		{
			Window::Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			for (const World::UpdateCallback callback : ActiveWorld->SystemUpdateCallbacks)
			{
				callback(1.2f);
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			Window::Update();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwTerminate();
		Window::DestroyWindow();
	}
}
