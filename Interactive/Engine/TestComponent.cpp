#include "TestComponent.h"
#include "TestComponent2.h"
#include "external/imgui/imgui.h"
#include "includes/CoreIncludes.h"

TestComponent::TestComponent() {}
TestComponent::~TestComponent() {}

void TestComponent::Initialize()
{
	Component::Initialize();

	InputController->BindKeyboardCallback(this);
}

void TestComponent::BeginPlay()
{
	Texture* newTexture = GetEnginePtr()->TextureSystem->CreateTexture("testTexture2", "test.jpg");
	Sprite2D* sprite = Owner->GetComponentOfType<Sprite2D>();
	sprite->AttachTexture(newTexture);
}

void TestComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);
}

void TestComponent::Render()
{
	Component::Render();

	bool asd = true;

	ImGui::SetNextWindowPos(ImVec2(0,0));
	ImGui::Begin("Hello", &asd, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::Button("Button");
	ImGui::End();
}

void TestComponent::KeyboardCallback()
{
	Component::KeyboardCallback();

	if (InputController->GetKeyState(Keys::W) == KeyActions::REPEAT || InputController->GetKeyState(Keys::W) == KeyActions::PRESS)
	{
		GetTransform()->Position.y += 0.01f;
	}

	if (InputController->GetKeyState(Keys::F) == KeyActions::PRESS)
	{
		GetTransform()->SetSize(glm::vec2(100.0f, 100.0f));
	}
}

void TestComponent::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

	InputController->UnbindKeyboardCallback(this);
}

Component* TestComponent::FactoryConstructor()
{
	Entity* entity = dynamic_cast<Entity*>(Interactive::GlobalObjectPointers["TestEntity"]);
	return entity->AddComponent<TestComponent2>();
}
