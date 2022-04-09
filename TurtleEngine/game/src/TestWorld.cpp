#include "TestWorld.h"

#include "components/SpriteComponent.h"
#include "components/TransformComponent.hpp"
#include "external/entt/entt.hpp"
#include "MovementComponent.hpp"
#include "MovementSystem.h"
#include "systems/render/Gl2DRendererSystem.h"

void TestWorld::OnWorldLoad()
{
	SystemUpdateCallbacks.push_back(TurtleCore::Gl2DRendererSystem::Render);
	SystemUpdateCallbacks.push_back(MovementSystem::MovementUpdate);

	const entt::entity entity = CreateEntity();
	TurtleCore::TransformComponent& transform = Registry.emplace<TurtleCore::TransformComponent>(entity);
	transform.Size = glm::vec2(5.0f, 5.0f);
	transform.Position = glm::vec2(1.0f, 1.0f);

	Registry.emplace<MovementComponent>(entity);
	Registry.emplace<TurtleCore::SpriteComponent>(entity, transform);

	const entt::entity entity2 = CreateEntity();
	TurtleCore::TransformComponent& transform2 = Registry.emplace<TurtleCore::TransformComponent>(entity2);
	transform2.Size = glm::vec2(5.0f, 5.0f);
	transform2.Position = glm::vec2(1.0f, 1.0f);

	Registry.emplace<TurtleCore::SpriteComponent>(entity2, transform);
}

void TestWorld::OnWorldUnloaded()
{
}