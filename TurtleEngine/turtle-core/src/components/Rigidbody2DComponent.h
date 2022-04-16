#pragma once
#include "../systems/physics/RigidbodyType.hpp"
#include "../external/entt/entt.hpp"

class b2Body;
namespace TurtleCore
{
	struct Rigidbody2DComponent
	{
		RigidbodyType BodyType = RigidbodyType::Dynamic;
		bool FixedRotation = true;

		b2Body* Body = nullptr;

		Rigidbody2DComponent(entt::entity entity);
		Rigidbody2DComponent(const Rigidbody2DComponent& other) = default;
	};
}