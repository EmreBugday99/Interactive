#pragma once

#include "world/World.h"
#include <mat4x4.hpp>


namespace TurtleEngine
{

	class Engine
	{
	public:
		static void Initialize(const char* gameName, int width, int height);
		static const char* GetGameName() { return GameName; }
		static void Start();
		static World& GetWorld() { return *ActiveWorld; }
		static glm::mat4 ProjectionMatrix;

		template <typename T, typename... TArgs>
		static World& LoadWorld(TArgs... args)
		{
			World* newWorld = new T(std::forward<TArgs>(args)...);
			newWorld->OnWorldLoad();

			ActiveWorld = newWorld;
			return *newWorld;
		}

	private:
		static bool IsInitialized;
		static const char* GameName;
		static World* ActiveWorld;

		static void Update();
	};
}
