#include "InteractiveObject.h"
#include "includes/CoreIncludes.h"
#include "reflection-system/ReflectionSystem.hpp"

InteractiveObject::InteractiveObject()
	: WaitingForDestruction(false), Engine(nullptr),
	Reflection(ReflectionSystem::CreateClassReflection<InteractiveObject>("InteractiveObject"))
{
}

InteractiveObject::~InteractiveObject()
{
	std::cout << "Uh" << std::endl;
}

void InteractiveObject::MarkForDestruction()
{
	if (WaitingForDestruction == true)
		return;
	WaitingForDestruction = true;
	OnMarkedForDestruction();

	GetEnginePtr()->GC->InsertObject(this);

	std::cout << "byee" << std::endl;
}

void InteractiveObject::OnMarkedForDestruction()
{
}