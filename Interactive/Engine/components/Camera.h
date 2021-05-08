#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../ecs/Component.h"

class Camera : public Component
{
public:
	glm::mat4 ProjectionMatrix;

	Camera();
	~Camera() override;

	void Update(float deltaTime) override;
	void Render() override;

};
