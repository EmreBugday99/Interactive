#include "TestComponent.h"
#include "TestComponent2.h"
#include "external/imgui/imgui.h"
#include "includes/CoreIncludes.h"

TestComponent::TestComponent() {}
TestComponent::~TestComponent() {}

void TestComponent::Initialize()
{
	Component::Initialize();
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

	if (InputController->IsKeyHold(Keys::W))
	{
		GetTransform()->Position.y += 0.01f;
	}
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

void TestComponent::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();
}

Component* TestComponent::FactoryConstructor()
{
	Entity* entity = dynamic_cast<Entity*>(Interactive::GlobalObjectPointers["TestEntity"]);
	return entity->AddComponent<TestComponent2>();
}
