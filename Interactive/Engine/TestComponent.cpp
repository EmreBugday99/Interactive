#include "TestComponent.h"
#include <iostream>

#include "components/Camera.h"
#include "includes/CoreIncludes.h"

TestComponent::TestComponent()
{
	OtherComponent = nullptr;
}

TestComponent::~TestComponent()
{
}

void TestComponent::BeginPlay()
{
	PrimitiveSprite2D::BeginPlay();

	InputController->BindKeyboardCallback(this);
}

void TestComponent::Update(float deltaTime)
{
	PrimitiveSprite2D::Update(deltaTime);

	//Engine->MainCamera->ProjectionMatrix = glm::ortho(Position.x / 2, Position.x * 2, Position.y / 2, Position.y * 2);

	//if (Position.x >= OtherComponent->Position.x && Position.y >= OtherComponent->Position.y &&
	//	Position.x < (OtherComponent->Position.x + OtherComponent->Size.x) &&
	//	Position.y < (OtherComponent->Position.y + OtherComponent->Size.y))
	//{
	//	std::cout << "Collision!" << std::endl;
	//}
}

void TestComponent::Render()
{
	PrimitiveSprite2D::Render();
}

void TestComponent::KeyboardCallback(Keys key, KeyActions actions)
{
	PrimitiveSprite2D::KeyboardCallback(key, actions);

	if (key == Keys::W)
	{
		Position.y += 0.0001f;
	}
	if (key == Keys::S)
	{
		Position.y -= 0.0001f;
	}
	if (key == Keys::A)
	{
		Position.x -= 0.0001f;
	}
	if (key == Keys::D)
	{
		Position.x += 0.0001f;
	}
}

bool TestComponent::IsColliding()
{
	return Position.x < (OtherComponent->Position.x + OtherComponent->Size.x)
		&& (Position.x + Size.x) > OtherComponent->Position.x
		&& Position.y < (OtherComponent->Position.y + OtherComponent->Size.y)
		&& (Position.y + Size.y) > OtherComponent->Position.y;
}