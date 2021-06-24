#include "GarbageCollector.h"
#include "includes/CoreIncludes.h"

GarbageCollector::GarbageCollector(Interactive* engine) : Engine(engine), ForceEnterThreshold(10) {}

GarbageCollector::~GarbageCollector() {}

void GarbageCollector::InsertObject(InteractiveObject* object)
{
	ObjectsToGarbageCollect.push_back(object);
}

void GarbageCollector::CollectGarbage()
{
	size_t objectIndex = ObjectsToGarbageCollect.size();

	while (objectIndex)
	{
		objectIndex--;

		delete(ObjectsToGarbageCollect[objectIndex]);
	}

	ObjectsToGarbageCollect.clear();
}