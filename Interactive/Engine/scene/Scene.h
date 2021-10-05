#pragma once

#include "../external/entt/entt.hpp"

namespace IE {
	struct Scene
	{
		Scene();
		~Scene();

		entt::registry Registry;

		entt::entity CreateEntity();
	};
}