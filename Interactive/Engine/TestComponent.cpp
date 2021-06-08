#include "TestComponent.h"
#include "TestComponent2.h"
#include "includes/CoreIncludes.h"

TestComponent::TestComponent() {}
TestComponent::~TestComponent() {}

void TestComponent::BeginPlay()
{
	PrimitiveSprite2D::BeginPlay();

	InputController->BindKeyboardCallback(this);

	Texture* newTexture = GetEnginePtr()->TextureSystem->CreateTexture("testTexture2", "test.jpg");
	AttachTexture(newTexture);
}

void TestComponent::Update(float deltaTime)
{
	PrimitiveSprite2D::Update(deltaTime);
}

void TestComponent::Render()
{
	PrimitiveSprite2D::Render();
}

void TestComponent::KeyboardCallback()
{
	PrimitiveSprite2D::KeyboardCallback();

	if (InputController->GetKeyState(Keys::W) == KeyActions::PRESS)
	{
		Position.y += 0.1f;
	}

	if (InputController->GetKeyState(Keys::S) == KeyActions::PRESS)
	{
		Position.y -= 0.1f;
	}
}

void TestComponent::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

	InputController->UnbindKeyboardCallback(this);
}