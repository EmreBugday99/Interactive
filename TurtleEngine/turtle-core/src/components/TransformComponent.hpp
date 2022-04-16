#pragma once
#include "glm/vec2.hpp"

namespace TurtleCore
{
	struct TransformComponent
	{
		glm::vec2 Size;
		glm::vec2 Position;

		TransformComponent() : Size(glm::vec2(10.0f, 10.0f)), Position(glm::vec2(0.0f, 0.0f)) {}

		TransformComponent(const TransformComponent& copied)
			: Size(glm::vec2(copied.Size.x, copied.Size.y)),
			Position(glm::vec2(copied.Position.x, copied.Position.y)) {}
	};
}
