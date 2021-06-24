#include "TestComponent2.h"
#include <iostream>

TestComponent2::TestComponent2()
{
	std::cout << "I am alive!" << std::endl;
}

void TestComponent2::Initialize()
{
	Sprite2D::Initialize();

	Texture* newTexture = GetEnginePtr()->TextureSystem->CreateTexture("smileyTexture", "smiley.jpg");
	AttachTexture(newTexture);
}

void TestComponent2::Update(float deltaTime)
{
	Sprite2D::Update(deltaTime);
}

void TestComponent2::Render()
{
	Sprite2D::Render();
}

void TestComponent2::KeyboardCallback()
{
	Sprite2D::KeyboardCallback();
}

void TestComponent2::SayHello()
{
	std::cout << "Hello!" << std::endl;
}

void TestComponent2::OnMarkedForDestruction()
{
	Sprite2D::OnMarkedForDestruction();
}
