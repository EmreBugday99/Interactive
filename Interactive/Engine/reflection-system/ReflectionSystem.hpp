#pragma once
#include "ClassReflection.hpp"
#include "TypeReflection.hpp"

class ReflectionSystem
{
public:
	template<class T>
	static TypeReflection CreateTypeReflection(const char* name)
	{
		TypeReflection newFieldReflection(name, sizeof(T));
		return newFieldReflection;
	}

	template<class T>
	static ClassReflection CreateClassReflection(const char* name)
	{
		ClassReflection newClassReflection(name, sizeof(T));
		return newClassReflection;
	}

	template<class T>
	static void UpdateClassReflection(ClassReflection& classType, const char* name)
	{
		classType.SetTypeName(name);
		classType.SizeInBytes = sizeof T;
	}

	static MethodReflection CreateMethodReflection(const char* name, TypeReflection returnType)
	{
		MethodReflection newMethodReflection(name, returnType);
		return newMethodReflection;
	}

	template<class T>
	static FieldReflection CreteFieldReflection(const char* name)
	{
		FieldReflection newFieldReflection(name, sizeof(T));
		return newFieldReflection;
	}
};