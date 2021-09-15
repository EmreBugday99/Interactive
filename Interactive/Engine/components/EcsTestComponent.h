#pragma once
#include "../ecs/Component.hpp"

class EcsTestComponent : public Interactive::Component
{
public:
	int TestInteger;

public:
	EcsTestComponent();
	EcsTestComponent(const EcsTestComponent& copyClass);

	void SayHello();
};
