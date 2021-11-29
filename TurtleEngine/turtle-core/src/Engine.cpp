#include "Engine.h"

#include "world/World.h"
#include <glm.hpp>
#include <ext.hpp>

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

		ProjectionMatrix = glm::ortho(0.f, (float)width, 0.0f, (float)height);

		ActiveWorld = nullptr;
		IsInitialized = true;
	}

	void Engine::Start()
	{
		Update();
	}

	void Engine::Update()
	{
		for (const World::UpdateCallback callback : ActiveWorld->SystemUpdateCallbacks)
		{
			callback(1.2f);
		}
	}
}