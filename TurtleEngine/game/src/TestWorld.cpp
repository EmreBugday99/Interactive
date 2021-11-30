#include "TestWorld.h"

#include "components/SpriteComponent.h"
#include "components/TransformComponent.hpp"
#include "external/entt/entt.hpp"
#include "graphics/opengl/Gl2DRendererSystem.h"

void TestWorld::OnWorldLoad()
{
	SystemUpdateCallbacks.push_back(TurtleCore::Gl2DRendererSystem::Render);

	entt::entity entity = CreateEntity();

	TurtleCore::TransformComponent& transform = Registry.emplace<TurtleCore::TransformComponent>(entity);
	transform.Size = glm::vec2(50.0f, 50.0f);
	transform.Position = glm::vec2(1.0f, 1.0f);

	TurtleCore::SpriteComponent& sprite = Registry.emplace<TurtleCore::SpriteComponent>(entity, transform);
}

void TestWorld::OnWorldUnloaded()
{
}
