#include "Transform.h"
#include "Sprite2D.h"
#include "../reflection-system/ReflectionSystem.hpp"

Transform::Transform()
	: Size(glm::vec2(10.0f, 10.0f)), Position(glm::vec3(0.0f, 0.0f, 0.0f))
{
	ReflectionSystem::AddInheritedClass<Transform>(Reflection, "Transform");
	ReflectionSystem::UpdateClassReflection<Transform>(Reflection, "Transform");
}

void Transform::Initialize()
{
	Component::Initialize();
}

void Transform::Update(float deltaTime)
{
	Component::Update(deltaTime);
}

void Transform::SetPosition(glm::vec3 newPosition)
{
	Position = newPosition;
}

void Transform::SetSize(glm::vec2 newSize)
{
	Size = newSize;
	
	Sprite2D* spriteComponent = static_cast<Sprite2D*>(Owner->GetComponentComplex("Sprite2D"));
	if (spriteComponent == nullptr)
	{
		std::cout << "Couldn't find Sprite2D component" << std::endl;
		return;
	}

	spriteComponent->UpdateSprite();
}