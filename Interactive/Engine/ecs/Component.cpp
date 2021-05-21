#include "Component.h"
#include "../includes/CoreIncludes.h"

Component::Component()
	: Owner(nullptr), InputController(nullptr), BeginPlayExecuted(false)
{
}
Component::~Component()
{
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
}
