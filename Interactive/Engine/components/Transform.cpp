#include "Transform.h"
#include "Sprite2D.h"

Transform::Transform()
{
	Size = glm::vec2(10.0f, 10.0f);
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Transform::BeginPlay()
{
	Component::BeginPlay();
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

	Component* spriteComponent = Owner->GetComponentOfType<Sprite2D>();

	if (spriteComponent != nullptr)
		dynamic_cast<Sprite2D*>(spriteComponent)->UpdateSprite();
}