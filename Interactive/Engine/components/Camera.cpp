#include "Camera.h"

Camera::Camera()
{
	ProjectionMatrix = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);
}
Camera::~Camera() {}

void Camera::Update(float deltaTime) {}
void Camera::Render() {}