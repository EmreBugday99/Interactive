#include "InteractiveObject.h"
#include "includes/CoreIncludes.h"
#include "reflection-system/ReflectionSystem.hpp"

InteractiveObject::InteractiveObject()
	: WaitingForDestruction(false), Engine(nullptr),
	Reflection(ReflectionSystem::CreateClassReflection<InteractiveObject>("InteractiveObject"))
{
	std::cout << "Hello!" << std::endl;
	ReflectionSystem::AddInheritedClass<InteractiveObject>(Reflection, "InteractiveObject");
}

InteractiveObject::~InteractiveObject()
{
}

void InteractiveObject::MarkForDestruction()
{
	if (WaitingForDestruction == true)
		return;
	WaitingForDestruction = true;
	OnMarkedForDestruction();

	GetEnginePtr()->GC->InsertObject(this);
}

void InteractiveObject::OnMarkedForDestruction()
{
}