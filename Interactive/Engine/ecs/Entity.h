#pragma once

#include "../external/entt/entt.hpp"

namespace IE {

	struct Entity
	{
	public:
		Entity();

	private:
		friend class EntityManager;
		entt::entity entityHandle;
	};
}