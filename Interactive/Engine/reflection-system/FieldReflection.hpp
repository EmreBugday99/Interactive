#pragma once
#include "TypeReflection.hpp"

struct FieldReflection : TypeReflection
{
	FieldReflection(const char* name, size_t size) : TypeReflection(name, size) {}
};
