#pragma once

#include "../external/entt/entt.hpp"
#include <vector>

namespace TurtleEngine {
	struct World
	{
		using UpdateCallback = void(*) (float deltaTime);

		entt::registry Registry;
		std::vector<UpdateCallback> SystemUpdateCallbacks;

		World();
		virtual ~World();

		virtual void OnWorldLoad();

		entt::entity CreateEntity();
	};
}