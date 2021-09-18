#pragma once

#include "../reflection/RuntimeReflection.hpp"
#include "../reflection/ReflectionMacros.hpp"

struct TestShit
{
	int asd;

	CLASS_DEFINITION(TestShit);
	RUNTIME_CLASS;

	TestShit()
	{
		asd = 123;
	}
};