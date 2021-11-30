#pragma once

#include "../external/entt/entt.hpp"
#include <vector>

namespace TurtleCore {
	struct World
	{
		using UpdateCallback = void(*) (float deltaTime);

		entt::registry Registry;
		std::vector<UpdateCallback> SystemUpdateCallbacks;

		World();
		virtual ~World();

		virtual void OnWorldLoad() = 0;
		virtual void OnWorldUnloaded() = 0;

		entt::entity CreateEntity();
	};
}