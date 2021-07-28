#include "ComponentFactory.h"

std::map<std::string, ComponentFactory::ConstructFunction> ComponentFactory::ConstructorMap;

ComponentFactory::ComponentFactory(Interactive* engine) : Engine(engine)
{
	ConstructorMap["null"] = &NullConstructor;
}

Component* ComponentFactory::NullConstructor(std::map<std::string, void*>& dataMap)
{
	return nullptr;
}