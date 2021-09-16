#pragma once
#include "../ecs/Component.hpp"

class TestComponent : public Interactive::Component
{
public:
	int TestInt;
	float TestFloat;

	TestComponent() : Component()
	{
		TestInt = 0;
		TestFloat = 0.0f;
	}
};