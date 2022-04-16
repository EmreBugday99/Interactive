#pragma once
#include "glm/vec2.hpp"

class b2Fixture;
namespace TurtleCore
{
	struct BoxCollider2DComponent
	{
		glm::vec2 Size = {0.01f, 0.01f};
		b2Fixture* Fixture = nullptr;

		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent& other) = default;
		
	};
}