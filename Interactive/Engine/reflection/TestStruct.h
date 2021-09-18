#pragma once
#include "../reflection/RuntimeReflection.hpp"
#include "../reflection/ReflectionMacros.hpp"

struct TestStruct
{
	int a;
	float b;
	CLASS_DEFINITION(TestStruct);
	RUNTIME_CLASS;

	TestStruct()
	{
		a = 10;
		b = 12.0f;
	}
	~TestStruct()
	{
		DESTROY_RUNTIME_CLASS;
	}
};