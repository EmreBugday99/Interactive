#include "PhysicsSystem2D.h"
#include "../../Engine.h"
#include "../../components/Rigidbody2DComponent.h"
#include "../../components/TransformComponent.hpp"
#include "include/box2d/b2_body.h"
#include "../../debugging/Logger.h"

void TurtleCore::PhysicsSystem2D::Update(float deltaTime)
{
	Engine::GetWorld().PhysicsWorld.Step(deltaTime, 6, 2);

	const auto& view = Engine::GetWorld().Registry.view<TransformComponent, Rigidbody2DComponent>();
	for (const entt::entity& entity : view)
	{
		TransformComponent& transform1 = view.get<TransformComponent>(entity);
		//const Rigidbody2DComponent& rigidbody = view.get<Rigidbody2DComponent>(entity);

		//transform.Position.x = rigidbody.Body->GetPosition().x;
		//transform.Position.y = rigidbody.Body->GetPosition().y;

		for (const entt::entity& entity2 : view)
		{
			if (entity2 == entity)
				continue;

			TransformComponent& transform2 = view.get<TransformComponent>(entity2);
			if (transform1.Position.x - transform1.Size.x < transform2.Position.x + transform2.Size.x &&
				transform1.Position.x + transform1.Size.x > transform2.Position.x - transform2.Size.x &&
				transform1.Position.y - transform1.Size.y < transform2.Position.y + transform2.Size.y &&
				transform1.Position.y + transform1.Size.y > transform2.Position.y - transform2.Size.y)
				Logger::Log("Collide!");
		}
	}
}
