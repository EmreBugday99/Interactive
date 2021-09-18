#pragma once
#include "ReflectionMacros.hpp"

namespace Interactive
{
	class ClassDefinition
	{
		//TODO: MAKE THIS ACCESS MODIFIER PRIVATE AFTER DEBUGGING IS OVER
	public:
		friend class RuntimeReflection;

		std::string DefinitionName;
		DEFINITION_ID  DefinitionId;
		DEFINITION_SIZE DefinitionSize;

		ClassDefinition(std::string className, const DEFINITION_ID typeId, const DEFINITION_SIZE classSize)
		{
			DefinitionName = className;
			DefinitionId = typeId;
			DefinitionSize = classSize;
		}

	public:
		//TODO: All the getters will be here
	};
}