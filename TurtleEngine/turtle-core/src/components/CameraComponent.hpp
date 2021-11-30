#pragma once

#include <ext.hpp>

namespace TurtleCore
{
	struct CameraComponent
	{
		glm::mat4 ProjectionMatrix;

		CameraComponent() : ProjectionMatrix(glm::ortho(0.0f, 0.0f, 0.0f, 0.0f)) {}
		CameraComponent(const CameraComponent& copied) = default;
	};
}