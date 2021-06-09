#include "TestComponent.h"
#include "TestComponent2.h"
#include "includes/CoreIncludes.h"

TestComponent::TestComponent() {}
TestComponent::~TestComponent() {}

void TestComponent::BeginPlay()
{
	Sprite2D::BeginPlay();

	InputController->BindKeyboardCallback(this);

	Texture* newTexture = GetEnginePtr()->TextureSystem->CreateTexture("testTexture2", "test.jpg");
	AttachTexture(newTexture);
}

void TestComponent::Update(float deltaTime)
{
	Sprite2D::Update(deltaTime);
}

void TestComponent::Render()
{
	Sprite2D::Render();
}

void TestComponent::KeyboardCallback()
{
	Sprite2D::KeyboardCallback();
}

void TestComponent::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

	InputController->UnbindKeyboardCallback(this);
}