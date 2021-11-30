#include "World.h"

namespace TurtleCore {
	World::World()
	{
	}

	World::~World()
	{
		Registry.clear();
	}

	entt::entity World::CreateEntity()
	{
		return Registry.create();
	}
}