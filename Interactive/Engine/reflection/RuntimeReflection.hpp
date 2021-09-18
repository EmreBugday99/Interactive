#pragma once
#include <string>
#include <vector>
#include "ClassDefinition.hpp"
#include "ReflectionMacros.hpp"
#include "RuntimeClass.hpp"

namespace Interactive
{
	class RuntimeReflection
	{
		inline static std::vector<ClassDefinition*> ClassTypes;
		inline static std::vector<RuntimeClass*> RuntimeClasses;

	public:

		static CLASS_ID_TYPE GenerateClassDefinition(std::string className)
		{
			const std::string typeName = GetClassName(className);
			const CLASS_ID_TYPE classId = GenerateClassId(typeName);

			const auto classType = new ClassDefinition(typeName.c_str(), classId);
			ClassTypes.push_back(classType);

			return classId;
		}

	private:
		static CLASS_ID_TYPE GenerateClassId(std::string className)
		{
			bool typeAlreadyExists = false;
			for (const ClassDefinition* classType : ClassTypes)
			{
				if (className == classType->ClassName)
					typeAlreadyExists = true;
			}

			if (typeAlreadyExists == false)
				return __COUNTER__;

			return -1;
		}

		static std::string GetClassName(std::string& classFile)
		{
			// Sanitizing file path from the class
			std::string delim = "\\";

			auto start = 0U;
			auto end = classFile.find(delim);
			while (end != std::string::npos)
			{
				start = end + delim.length();
				end = classFile.find(delim, start);
			}

			std::string pathCleanString = classFile.substr(start, end);

			// Sanitizing file extension (.cpp, .h, .hpp etc.) from class

			delim = ".";

			start = 0U;
			end = pathCleanString.find(delim);
			return pathCleanString.substr(start, end);
		}

		static void BeforeRuntimeClassPtrChange(RuntimeClass* oldPtr, RuntimeClass* updatedPtr)
		{
			for (RuntimeClass* runtimeClass : RuntimeClasses)
			{
				if (runtimeClass != oldPtr)
					continue;

				runtimeClass = updatedPtr;
				break;
			}
		}
	};
}