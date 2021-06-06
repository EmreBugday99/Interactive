#include "TestComponent.h"
#include "TestComponent2.h"
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

	if (InputController->GetKeyState(Keys::W) == KeyActions::PRESS)
	{
		Position.y += 0.1f;

		Component* asd = Owner->GetComponent<TestComponent2>();
		if (asd == nullptr) return;

		TestComponent2* comp2 = dynamic_cast<TestComponent2*>(asd);
		if (comp2 != nullptr)
			comp2->SayHello();
	}

	if (InputController->GetKeyState(Keys::F) == KeyActions::PRESS)
	{
		Component* asd = Owner->GetComponent<TestComponent2>();
		if (asd == nullptr) return;

		asd->MarkForDestruction();
	}
}

void TestComponent::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

	InputController->UnbindKeyboardCallback(this);
}