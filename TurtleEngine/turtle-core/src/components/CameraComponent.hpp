#pragma once

#include <glm/ext.hpp>

namespace TurtleCore
{
	struct CameraComponent
	{
		glm::mat4 ProjectionMatrix;

		CameraComponent(float left, float right, float bottom, float top) : ProjectionMatrix(glm::ortho(left, right, bottom, top)) {}

		CameraComponent(const CameraComponent& copied) = default;
	};
}