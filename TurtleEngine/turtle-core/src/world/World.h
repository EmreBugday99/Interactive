#pragma once

#include "../external/entt/entt.hpp"
#include <vector>
#include "include/box2d/b2_world.h"

namespace TurtleCore {
	struct World
	{
		using UpdateCallback = void(*) (float deltaTime);

		entt::registry Registry;
		std::vector<UpdateCallback> SystemUpdateCallbacks;
		b2World PhysicsWorld;
		bool IsLoaded = false;;

		World();
		virtual ~World();

		virtual void OnWorldLoad() = 0;
		virtual void OnWorldUnloaded() = 0;

		entt::entity CreateEntity();
	};
}
