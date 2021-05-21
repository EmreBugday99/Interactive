#include "InteractiveObject.h"
#include "Interactive.h"

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
}

void InteractiveObject::OnMarkedForDestruction()
{
}