#include "TestComponent2.h"
#include "includes/CoreIncludes.h"

TestComponent2::~TestComponent2()
{
}

void TestComponent2::Initialize()
{
}

void TestComponent2::BeginPlay()
{
}

void TestComponent2::Update(float deltaTime)
{
}

void TestComponent2::Render()
{
	Component::Render();

	ImGui::Begin("hello");
	ImGui::Text("Lorem Ipsum");
	ImGui::Text("Dolor Sit Amet");
	ImGui::End();
}

void TestComponent2::OnMarkedForDestruction()
{
}
