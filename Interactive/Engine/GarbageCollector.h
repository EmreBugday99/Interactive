#pragma once
#include <vector>

class Interactive;
class InteractiveObject;
class GarbageCollector
{
public:
	Interactive* Engine;
	size_t ForceEnterThreshold;

	GarbageCollector(Interactive* engine);
	~GarbageCollector();

	void InsertObject(InteractiveObject* object);
	void CollectGarbage();

	size_t GetGCQueueSize() { return ObjectsToGarbageCollect.size(); }

private:
	std::vector<InteractiveObject*> ObjectsToGarbageCollect;
};
