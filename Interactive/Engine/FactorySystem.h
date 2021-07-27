#pragma once
#include "includes/CoreIncludes.h"

class FactorySystem
{
public:
	typedef Component* (*ConstructFunction)(void);

	Interactive* Engine;
	
	static std::map<std::string, ConstructFunction> ConstructorMap;
	FactorySystem(Interactive* engine);

private:
	static Component* NullConstructor();
};
