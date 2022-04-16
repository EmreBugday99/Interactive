#include "Rigidbody2DComponent.h"
#include "../Engine.h"
#include "../debugging/Logger.h"
#include "TransformComponent.hpp"
#include "include/box2d/b2_body.h"
#include "../systems/physics/RigidbodyTypeConverter.h"
#include "BoxCollider2DComponent.hpp"
#include "include/box2d/b2_polygon_shape.h"
#include "include/box2d/b2_fixture.h"

TurtleCore::Rigidbody2DComponent::Rigidbody2DComponent(const entt::entity entity)
{
	entt::registry& registry = Engine::GetWorld().Registry;

	if (registry.valid(entity) == false)
	{
		Logger::LogError("Invalid entity!");
	}

	if (registry.all_of<TransformComponent>(entity) == false)
	{
		Logger::LogError("Rigidbody requires Transform Component!");
		return;
	}
	const auto& transform = registry.get<TransformComponent>(entity);

	b2BodyDef bodyDefinition;
	bodyDefinition.type = RigidbodyTypeConverter::ConvertToBox2D(BodyType);
	bodyDefinition.position.Set(transform.Position.x, transform.Position.y);
	bodyDefinition.angle = 0.0f;

	Body = Engine::GetWorld().PhysicsWorld.CreateBody(&bodyDefinition);
	Body->SetFixedRotation(FixedRotation);

	if (registry.all_of<BoxCollider2DComponent>(entity))
	{
		const auto& collider = registry.get<BoxCollider2DComponent>(entity);

		b2PolygonShape shape;
		shape.SetAsBox(collider.Size.x, collider.Size.y);
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = collider.Density;
		fixture.friction = collider.Friction;
		fixture.restitution = collider.Restitution;
		fixture.restitutionThreshold = collider.RestitutionThreshold;

		Body->CreateFixture(&fixture);
	}
}