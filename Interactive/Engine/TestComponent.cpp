#include "TestComponent.h"
#include "TestComponent2.h"
#include "includes/CoreIncludes.h"

TestComponent::TestComponent() {}
TestComponent::~TestComponent() {}

void TestComponent::BeginPlay()
{
	PrimitiveSprite2D::BeginPlay();

	InputController->BindKeyboardCallback(this);

	if (Owner->HasComponent<TestComponent2>() == false)
	{
		std::cout << "No Has Component" << std::endl;
		Owner->AddComponent<TestComponent2>();
	}

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

		Component* asd = Owner->GetComponentOfType<TestComponent2>();
		if (asd == nullptr)
		{
			std::cout << "asd is NULLPTR" << std::endl;
			return;
		}

		TestComponent2* comp2 = dynamic_cast<TestComponent2*>(asd);
		if (comp2 != nullptr)
			comp2->SayHello();
	}

	if (InputController->GetKeyState(Keys::F) == KeyActions::PRESS)
	{
		Owner->AddComponent<TestComponent2>();
	}

	if (InputController->GetKeyState(Keys::E) == KeyActions::PRESS)
	{
		std::vector<TestComponent2*> components = Owner->GetComponentsOfType<TestComponent2>();

		for (TestComponent2* testComp : components)
		{
			testComp->SayHello();
		}
	}

	if (InputController->GetKeyState(Keys::ESCAPE) == KeyActions::PRESS)
	{
		Owner->MarkForDestruction();
	}
}

void TestComponent::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

	InputController->UnbindKeyboardCallback(this);
}