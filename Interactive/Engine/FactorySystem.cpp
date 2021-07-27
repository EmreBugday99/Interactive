#include "FactorySystem.h"

std::map<std::string, FactorySystem::ConstructFunction> FactorySystem::ConstructorMap;

FactorySystem::FactorySystem(Interactive* engine) : Engine(engine)
{
	ConstructorMap.emplace("null", &NullConstructor);
}

Component* FactorySystem::NullConstructor()
{
	return nullptr;
}