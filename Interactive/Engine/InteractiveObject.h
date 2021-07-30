#pragma once
#include "reflection-system/ClassReflection.hpp"

class Interactive;
class InteractiveObject
{
private:
	bool WaitingForDestruction;
	Interactive* Engine;

public:
	ClassReflection Reflection;
	
	InteractiveObject();
	virtual ~InteractiveObject();

	bool IsWaitingForDestruction() const { return WaitingForDestruction; }
	void MarkForDestruction();

	Interactive* GetEnginePtr() const { return Engine; }

protected:
	virtual void OnMarkedForDestruction();
	void SetEnginePtr(Interactive* engine) { Engine = engine; }
};
