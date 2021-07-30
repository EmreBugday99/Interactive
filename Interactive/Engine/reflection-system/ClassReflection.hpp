#pragma once
#include <vector>


#include "FieldReflection.hpp"
#include "MethodReflection.hpp"
#include "TypeReflection.hpp"

struct ClassReflection : TypeReflection
{
	std::vector<FieldReflection> Fields;
	std::vector<MethodReflection> Methods;
	
	ClassReflection(const char* className, size_t classSize)
		: TypeReflection(className, classSize) {}
};
