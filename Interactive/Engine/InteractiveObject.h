#pragma once

class Interactive;
class InteractiveObject
{
private:
	bool WaitingForDestruction;
	Interactive* Engine;

public:
	InteractiveObject();
	virtual ~InteractiveObject();

	bool IsWaitingForDestruction() const { return WaitingForDestruction; }
	void MarkForDestruction();

	Interactive* GetEnginePtr() const { return Engine; }

protected:
	virtual void OnMarkedForDestruction();
	void SetEnginePtr(Interactive* engine) { Engine = engine; }
};
