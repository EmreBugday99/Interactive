#pragma once

#include "world/World.h"
#include <mat4x4.hpp>

#include "input/InputManager.h"

namespace TurtleCore
{
	class BaseWindow;
	class Engine
	{
	public:
		static glm::mat4 ProjectionMatrix;
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
			newWorld->OnWorldLoad();

			if (ActiveWorld != nullptr)
				ActiveWorld->OnWorldUnloaded();

			const World* oldActiveWorld = ActiveWorld;
			ActiveWorld = newWorld;
			delete oldActiveWorld;

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
