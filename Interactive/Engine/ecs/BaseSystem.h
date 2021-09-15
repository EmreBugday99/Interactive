#pragma once
#include <vector>

class BaseSystem
{
private:
	std::vector<unsigned int> ComponentTypes;

public:
	BaseSystem(const std::vector<unsigned int>& componentTypes)
		:ComponentTypes(componentTypes) {}

	virtual void Update(const float deltaTime) {}
};
