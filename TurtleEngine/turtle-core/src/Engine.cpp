#include "Engine.h"

#include "world/World.h"
#include "debugging/Logger.h"
#include "glm/ext.hpp"
#include "graphics/opengl/os-windows/GlWindowsWindow.h"

namespace TurtleCore
{
	bool Engine::IsInitialized;
	bool Engine::HasStarted;
	World* Engine::ActiveWorld;
	glm::mat4 Engine::ProjectionMatrix;
	BaseWindow* Engine::GameWindow;
	InputManager* Engine::InputSystem;

	void Engine::Initialize(bool& successful, const char* gameName, int width, int height)
	{
		successful = false;
		HasStarted = false;

		if (IsInitialized)
			return;

		ProjectionMatrix = glm::ortho(0.f, static_cast<float>(width), 0.0f, static_cast<float>(height));
		InputSystem = new InputManager();

#ifdef TURTLE_OS_WINDOWS
		GameWindow = new GlWindowsWindow();
		GameWindow->Initialize(successful, gameName, width, height);
		if (successful == false)
		{
			Logger::LogError("Failed to initialize Game Window!");
			return;
		}
#else
		Logger::LogError("Only Windows is supported for the time being!");
		return;
#endif

		GameWindow->ConstructWindow(successful);
		if (successful == false)
		{
			Logger::LogError("Failed to construct Game Window!");
			return;
		}

		ActiveWorld = nullptr;
		IsInitialized = true;
	}

	void Engine::Start()
	{
		bool successful = false;
		if (HasStarted == true)
		{
			Logger::LogError("Attempted to start engine when already started!");
			return;
		}

		if (ActiveWorld == nullptr)
		{
			Logger::LogError("A world must be loaded before starting!");
			return;
		}

		HasStarted = true;
		Update();
	}

	void Engine::Stop()
	{
		GameWindow->CloseWindow();
	}

	void Engine::Update()
	{
		while (GameWindow->IsOpen())
		{
			GameWindow->Clear();
			for (const World::UpdateCallback callback : ActiveWorld->SystemUpdateCallbacks)
			{
				callback(1.2f);
			}
			GameWindow->Update();
		}

		OnStop();
	}

	void Engine::OnStop()
	{
		delete GameWindow;
	}
}