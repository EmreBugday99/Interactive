#include "TestComponent2.h"
#include <iostream>

TestComponent2::TestComponent2()
{
	std::cout << "I am alive!" << std::endl;
}

void TestComponent2::BeginPlay()
{
	PrimitiveSprite2D::BeginPlay();

	Texture* newTexture = GetEnginePtr()->TextureSystem->CreateTexture("smileyTexture", "smiley.jpg");
	AttachTexture(newTexture);
}

void TestComponent2::Update(float deltaTime)
{
	PrimitiveSprite2D::Update(deltaTime);
	
	if (Size.y <= 100.0f)
	{
		Size.y -= 1.0f;
	}
	if(Size.y <= 50.0f)
	{
		Size.y += 50.0f;
	}
}

void TestComponent2::Render()
{
	PrimitiveSprite2D::Render();
}

void TestComponent2::KeyboardCallback()
{
	PrimitiveSprite2D::KeyboardCallback();

	std::cout << "2 callback" << std::endl;
}

void TestComponent2::SayHello()
{
	std::cout << "Hello!" << std::endl;
}

void TestComponent2::OnMarkedForDestruction()
{
	PrimitiveSprite2D::OnMarkedForDestruction();
}
