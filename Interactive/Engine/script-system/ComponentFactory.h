#pragma once
#include "../includes/CoreIncludes.h"

class ComponentFactory
{
public:
	typedef Component* (*ConstructFunction)(std::map<std::string, void*>&);

	Interactive* Engine;
	
	static std::map<std::string, ConstructFunction> ConstructorMap;
	ComponentFactory(Interactive* engine);

private:
	static Component* NullConstructor(std::map<std::string, void*>& dataMap);
};
