#include "InteractiveObject.h"
#include "includes/CoreIncludes.h"

InteractiveObject::InteractiveObject()
	: WaitingForDestruction(false), Engine(nullptr)
{
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