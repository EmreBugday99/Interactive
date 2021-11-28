#include "TestWorld.h"

#include "components/SpriteComponent.h"
#include "components/TransformComponent.hpp"
#include "renderer/RendererSystem2D.h"

void TestWorld::OnWorldLoad()
{
	entt::entity entity = Registry.create();
	TurtleEngine::TransformComponent& transform = Registry.emplace<TurtleEngine::TransformComponent>(entity);

	transform.Size.x = 100.0f;
	transform.Size.y = 50.0f;

	transform.Position.x = 0.2f;
	transform.Position.y = 1.1f;

	TurtleEngine::SpriteComponent& sprite = Registry.emplace<TurtleEngine::SpriteComponent>(entity, transform);

	entt::entity entity2 = Registry.create();
	TurtleEngine::TransformComponent& transform2 = Registry.emplace<TurtleEngine::TransformComponent>(entity2);

	transform2.Size.x = 100.0f;
	transform2.Size.y = 50.0f;

	transform2.Position.x = 0.2f;
	transform2.Position.y = 1.1f;

	TurtleEngine::SpriteComponent& sprite2 = Registry.emplace<TurtleEngine::SpriteComponent>(entity2, transform2);

	SystemUpdateCallbacks.push_back(TurtleEngine::RendererSystem2D::Render);
}
