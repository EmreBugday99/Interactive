#include "Camera.h"

Camera::Camera()
{
	ProjectionMatrix = glm::ortho(0.0f, 16.0f, 0.0f, 16.0f);
}
Camera::~Camera() {}

void Camera::Update(float deltaTime) {}
void Camera::Render() {}