#include "Camera.h"

Camera::Camera()
	: ProjectionMatrix(glm::ortho(0.0f, 2.0f, 0.0f, 2.0f))
{
}
Camera::~Camera() {}

void Camera::Update(float deltaTime) {}
void Camera::Render() {}

void Camera::SetProjection(glm::vec4 projection)
{
	ProjectionMatrix = glm::ortho(projection.x, projection.y, projection.z, projection.w);
}