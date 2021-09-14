#include "Camera.h"

#include "../reflection-system/ReflectionSystem.hpp"

// Placeholder, ProjectionMatrix will reset at BeginPlay.
Camera::Camera() : ProjectionMatrix(glm::ortho(0.0f, 0.0f, 0.0f, 0.0f))
{
	ReflectionSystem::AddInheritedClass<Camera>(Reflection, "Camera");
	ReflectionSystem::UpdateClassReflection<Camera>(Reflection, "Camera");
}

Camera::~Camera() {}

void Camera::Update(float deltaTime) { Component::Update(deltaTime); }
void Camera::Render() { Component::Render(); }

void Camera::SetProjection(glm::vec4 projection)
{
	ProjectionMatrix = glm::ortho(projection.x, projection.y, projection.z, projection.w);
}

void Camera::Initialize()
{
	Component::Initialize();

	Window* gameWindow = GetEnginePtr()->GameWindow;

	SetProjection(glm::vec4(0.0f, gameWindow->GetWidth(), 0.0f, gameWindow->GetHeight()));
}

void Camera::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

	if (GetEnginePtr()->MainCamera == this)
		GetEnginePtr()->MainCamera = nullptr;
}