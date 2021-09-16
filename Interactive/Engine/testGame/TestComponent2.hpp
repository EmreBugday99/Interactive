#pragma once

#include <string>
#include "../ecs/Component.hpp"

class TestComponent2 : public Interactive::Component
{
public:

	std::string TestString;
};