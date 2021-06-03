#pragma once
#include "../includes/CoreIncludes.h"

class Camera : public Component
{
public:
	glm::mat4 ProjectionMatrix;

	Camera();
	~Camera() override;

	void Update(float deltaTime) override;
	void Render() override;

	void SetProjection(glm::vec4 projection);

protected:
	void OnMarkedForDestruction() override;
};
