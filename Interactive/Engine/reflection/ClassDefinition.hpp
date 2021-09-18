#pragma once
#include "ReflectionMacros.hpp"

namespace Interactive
{
	class ClassDefinition
	{
		friend class RuntimeReflection;

		const char* ClassName;
		CLASS_ID_TYPE  TypeId;
		CLASS_SIZE ClassSize;

		ClassDefinition(const char* className, CLASS_ID_TYPE typeId)
		{
			ClassName = className;
			TypeId = typeId;
		}

	public:
		//TODO: All the getters will be here
	};
}