#include "TestComponent2.h"

#include <iostream>

void TestComponent2::BeginPlay()
{
	Component::BeginPlay();
}

void TestComponent2::Update(float deltaTime)
{
	Component::Update(deltaTime);
}

void TestComponent2::Render()
{
	Component::Render();
}

void TestComponent2::KeyboardCallback()
{
	Component::KeyboardCallback();
}

void TestComponent2::SayHello()
{
	std::cout << "Hello!" << std::endl;
}

void TestComponent2::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();
}
