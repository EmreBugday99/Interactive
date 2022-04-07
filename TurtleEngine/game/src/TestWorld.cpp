#include "TestWorld.h"

#include "components/SpriteComponent.h"
#include "components/TransformComponent.hpp"
#include "external/entt/entt.hpp"
#include "graphics/opengl/Gl2DRendererSystem.h"
#include "MovementComponent.hpp"
#include "MovementSystem.h"

void TestWorld::OnWorldLoad()
{
	SystemUpdateCallbacks.push_back(TurtleCore::Gl2DRendererSystem::Render);
	SystemUpdateCallbacks.push_back(MovementSystem::MovementUpdate);

	entt::entity entity = CreateEntity();

	TurtleCore::TransformComponent& transform = Registry.emplace<TurtleCore::TransformComponent>(entity);

	transform.Size = glm::vec2(10.0f, 10.0f);
	transform.Position = glm::vec2(1.0f, 1.0f);

	MovementComponent& movement = Registry.emplace<MovementComponent>(entity);
	TurtleCore::SpriteComponent& sprite = Registry.emplace<TurtleCore::SpriteComponent>(entity, transform);

	entt::entity entity2 = CreateEntity();

	TurtleCore::TransformComponent& transform2 = Registry.emplace<TurtleCore::TransformComponent>(entity2);
	transform2.Size = glm::vec2(10.0f, 10.0f);
	transform2.Position = glm::vec2(1.2f, 1.2f);

	TurtleCore::SpriteComponent& sprite2 = Registry.emplace<TurtleCore::SpriteComponent>(entity2, transform);
}

void TestWorld::OnWorldUnloaded()
{
}
