#pragma once
#include "components/CameraComponent.hpp"
#include "world/World.h"
#include "input/InputManager.h"

namespace TurtleCore
{
	class BaseWindow;
	class Engine
	{
	public:
		static CameraComponent Camera;
		static BaseWindow* GameWindow;
		static InputManager* InputSystem;

	public:
		static void Initialize(bool& successful, const char* gameName, int width, int height);
		static void Start();
		static void Stop();
		static World& GetWorld() { return *ActiveWorld; }

		template <typename T, typename... TArgs>
		static World& LoadWorld(TArgs... args)
		{
			World* newWorld = new T(std::forward<TArgs>(args)...);

			if (ActiveWorld != nullptr)
			{
				ActiveWorld->OnWorldUnloaded();
				ActiveWorld->Registry.clear();
			}

			const World* oldActiveWorld = ActiveWorld;
			ActiveWorld = newWorld;
			delete oldActiveWorld;

			newWorld->OnWorldLoad();
			newWorld->IsLoaded = true;
			return *ActiveWorld;
		}

	private:
		static bool IsInitialized;
		static bool HasStarted;
		static World* ActiveWorld;

		static void Update();
		static void OnStop();
	};
}
