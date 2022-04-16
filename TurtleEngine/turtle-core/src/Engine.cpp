#include "Engine.h"

#include "world/World.h"
#include "debugging/Logger.h"
#include "graphics/opengl/os-windows/GlWindowsWindow.h"

namespace TurtleCore
{
	bool Engine::IsInitialized;
	bool Engine::HasStarted;
	World* Engine::ActiveWorld;
	CameraComponent Engine::Camera(CameraComponent{ 0.0f, 0.0f, 0.0f, 0.0f });

	BaseWindow* Engine::GameWindow;
	InputManager* Engine::InputSystem;

	void Engine::Initialize(bool& successful, const char* gameName, int width, int height)
	{
		successful = false;
		HasStarted = false;

		if (IsInitialized)
			return;

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

		const float aspect = static_cast<float>(GameWindow->WindowWidth) / static_cast<float>(GameWindow->WindowHeight);
		const float halfHeight = static_cast<float>(GameWindow->WindowWidth) / 2.0f;
		const float halfWidth = static_cast<float>(GameWindow->WindowHeight) * aspect;
		Camera.ProjectionMatrix = glm::ortho(0.0f, static_cast<float>(GameWindow->WindowWidth), 0.0f, static_cast<float>(GameWindow->WindowHeight), 0.0001f, 3000.0f);
		//Camera.ProjectionMatrix = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);
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
				callback(0.01f);
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