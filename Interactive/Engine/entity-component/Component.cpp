#include "Component.h"

#include <iostream>

#include "../includes/CoreIncludes.h"

Component::Component()
	: Owner(nullptr), InputController(nullptr), BeginPlayExecuted(false)
{
	std::cout << "Created Component\n";
}
Component::~Component()
{
	std::cout << "Deleted component" << std::endl;
}
void Component::BeginPlay()
{
	BeginPlayExecuted = true;
}
void Component::Update(float deltaTime)
{
}
void Component::Render()
{
}
void Component::KeyboardCallback()
{
}

void Component::OnMarkedForDestruction()
{
	InteractiveObject::OnMarkedForDestruction();

	std::cout << "Component marked for destruction \n";

	Owner->ComponentsWaitingToLeave.push_back(this);
}
