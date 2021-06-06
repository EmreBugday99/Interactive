#include "Camera.h"

// Placeholder, ProjectionMatrix will be resetted at Beginplay.
Camera::Camera() : ProjectionMatrix(glm::ortho(0.0f, 0.0f, 0.0f, 0.0f)) {}
Camera::~Camera() {}

void Camera::Update(float deltaTime) {}
void Camera::Render() {}

void Camera::SetProjection(glm::vec4 projection)
{
	ProjectionMatrix = glm::ortho(projection.x, projection.y, projection.z, projection.w);
}

void Camera::BeginPlay()
{
	Component::BeginPlay();

	Window* gameWindow = GetEnginePtr()->GameWindow;

	SetProjection(glm::vec4(0.0f, gameWindow->GetWidth(), 0.0f, gameWindow->GetHeight()));
}

void Camera::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

	if (GetEnginePtr()->MainCamera == this)
		GetEnginePtr()->MainCamera = nullptr;
}