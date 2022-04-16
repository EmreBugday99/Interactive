#include "World.h"

namespace TurtleCore {
	World::World() : PhysicsWorld({ 0.0f, -10.0f }) {}

	World::~World()
	{
		Registry.clear();
	}

	void World::OnWorldLoad() {}

	void World::OnWorldUnloaded() {}

	entt::entity World::CreateEntity()
	{
		return Registry.create();
	}
}