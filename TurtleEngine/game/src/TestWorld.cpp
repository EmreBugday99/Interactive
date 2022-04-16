#include "TestWorld.h"

#include "Engine.h"
#include "MovementComponent.hpp"
#include "components/SpriteComponent.h"
#include "components/TransformComponent.hpp"
#include "external/entt/entt.hpp"
#include "MovementSystem.h"
#include "systems/physics/PhysicsSystem2D.h"
#include "systems/render/Gl2DRendererSystem.h"
#include "components/BoxCollider2DComponent.hpp"
#include "components/Rigidbody2DComponent.h"
#include "debugging/Logger.h"
#include "include/box2d/b2_body.h"

void TestWorld::OnWorldLoad()
{
	SystemUpdateCallbacks.push_back(TurtleCore::Gl2DRendererSystem::Update);
	SystemUpdateCallbacks.push_back(MovementSystem::MovementUpdate);
	SystemUpdateCallbacks.push_back(TurtleCore::PhysicsSystem2D::Update);

	//const auto entity = CreateEntity();
	//TurtleCore::TransformComponent& transform = Registry.emplace<TurtleCore::TransformComponent>(entity);
	//Registry.emplace<TurtleCore::SpriteComponent>(entity, transform);

	//for (int i = 0; i < 99; ++i)
	//{
	//	static float posY = 0.0f;
	//	const auto entity = CreateEntity();

	//	TurtleCore::TransformComponent& transform = Registry.emplace<TurtleCore::TransformComponent>(entity);
	//	transform.Position.y = posY;

	//	Registry.emplace<TurtleCore::SpriteComponent>(entity, transform);
	//	posY += 100.0f;
	//}

	const auto entity2 = CreateEntity();
	TurtleCore::TransformComponent& transform2 = Registry.emplace<TurtleCore::TransformComponent>(entity2);
	Registry.emplace<TurtleCore::SpriteComponent>(entity2, transform2);
	Registry.emplace<TurtleCore::BoxCollider2DComponent>(entity2);
	Registry.emplace<TurtleCore::Rigidbody2DComponent>(entity2, entity2);
	Registry.emplace<MovementComponent>(entity2);

	const auto entity3 = CreateEntity();
	TurtleCore::TransformComponent& transform3 = Registry.emplace<TurtleCore::TransformComponent>(entity3);
	transform3.Position.y = -1.0f;

	Registry.emplace<TurtleCore::SpriteComponent>(entity3, transform3).Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	Registry.emplace<TurtleCore::BoxCollider2DComponent>(entity3);
	TurtleCore::Rigidbody2DComponent& rigidbody3 = Registry.emplace<TurtleCore::Rigidbody2DComponent>(entity3, entity3);
	rigidbody3.Body->SetType(b2_staticBody);
}

void TestWorld::OnWorldUnloaded()
{
}