#include "TestComponent.h"
#include <iostream>
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

	if (InputController->GetKeyState(Keys::W) == KeyActions::REPEAT)
	{
		Position.y += 0.01f;
	}
	if (InputController->GetKeyState(Keys::S) == KeyActions::REPEAT)
	{
		Position.y -= 0.01f;
	}
	if (InputController->GetKeyState(Keys::F) == KeyActions::PRESS)
	{
		Owner->MarkForDestruction();
	}
	if (InputController->GetKeyState(Keys::ENTER) == KeyActions::PRESS)
	{
		Entity* newEntity = GetEnginePtr()->ECManager->CreateEntity("Test Entity For GC");
		newEntity->AddComponent<PrimitiveSprite2D>();
		testEntities.push_back(newEntity);
		std::cout << "CREATED ENTITY\n";
	}
	if (InputController->GetKeyState(Keys::J) == KeyActions::PRESS)
	{
		for (Entity* entity : testEntities)
		{
			entity->MarkForDestruction();
		}
		testEntities.clear();
		Owner->MarkForDestruction();
	}

	if (InputController->GetKeyState(Keys::Z) == KeyActions::PRESS)
	{
		OtherComponent->MarkForDestruction();
	}
}

void TestComponent::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

	InputController->UnbindKeyboardCallback(this);
}