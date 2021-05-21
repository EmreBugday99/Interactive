#include "Component.h"
#include "../includes/CoreIncludes.h"

Component::Component()
	: Owner(nullptr), Engine(nullptr),
	InputController(nullptr), BeginPlayExecuted(false)
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

void Component::DestroyComponent()
{
	MarkedForDestruction = true;

	//size_t componentIndex = Owner->Components.size();

	//while (componentIndex)
	//{
	//	componentIndex--;

	//	if (this == Owner->Components[componentIndex])
	//	{
	//		Owner->Components.erase(Owner->Components.begin() + componentIndex);
	//		break;
	//	}
	//}
}