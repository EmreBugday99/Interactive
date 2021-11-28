#include "World.h"

namespace TurtleEngine {
	World::World()
	{
	}

	World::~World()
	{
		Registry.clear();
	}

	void World::OnWorldLoad()
	{}

	entt::entity World::CreateEntity()
	{
		return Registry.create();
	}
}