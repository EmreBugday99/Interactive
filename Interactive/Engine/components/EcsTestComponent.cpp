#include "EcsTestComponent.h"

#include <iostream>

EcsTestComponent::EcsTestComponent() : Component()
{
	TestInteger = 0;
}

EcsTestComponent::EcsTestComponent(const EcsTestComponent& copyClass) : Component(copyClass)
{
	TestInteger = copyClass.TestInteger;
}

void EcsTestComponent::SayHello()
{
	std::cout << "Hello from test component!" << std::endl;
}