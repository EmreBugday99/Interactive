#pragma once
#include <vector>
#include <functional>

struct MethodReflection
{
	TypeReflection ReturnType;
	std::vector<TypeReflection> Parameters;

	MethodReflection(const char* methodName, TypeReflection returnType)
		: ReturnType(returnType), MethodName(methodName),
		HashedName(std::hash<std::string>{}(methodName)) {}

	void SetMethodName(const char* name)
	{
		MethodName = name;
		HashedName = std::hash<std::string>{}(name);
	}
	const char* GetMethodName() const { return MethodName; }
	size_t GetHashedName() const { return HashedName; }

private:
	const char* MethodName;
	size_t HashedName;
};