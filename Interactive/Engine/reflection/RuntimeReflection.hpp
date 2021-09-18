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
		inline static std::vector<ClassDefinition*> ClassDefinitions;
		inline static std::vector<RuntimeClass*> RuntimeClasses;

	public:

		static DEFINITON_ID GenerateClassDefinition(std::string className, DEFINITION_SIZE classSize)
		{
			const std::string typeName = GetClassName(className);
			const DEFINITON_ID classId = GenerateClassDefinitionId(typeName);

			// If a class definition already exists for a certain type we return -1 indicating instruction failure.
			if (classId == -1)
				return classId;

			const auto classType = new ClassDefinition(typeName, classId, classSize);
			ClassDefinitions.push_back(classType);

			return classId;
		}

		static ClassDefinition* FetchClassDefinition(DEFINITON_ID classId)
		{
			for (ClassDefinition* classDef : ClassDefinitions)
			{
				if (classId == classDef->DefinitionId)
					return classDef;
			}

			return nullptr;
		}

		template<typename T>
		static DEFINITION_SIZE GetClassSize() { return sizeof(T); }

	private:
		// *** Class Definition Start ***

		static DEFINITON_ID GenerateClassDefinitionId(std::string className)
		{
			bool typeAlreadyExists = false;
			for (const ClassDefinition* classType : ClassDefinitions)
			{
				if (className == classType->DefinitionName)
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

		// *** Class Definition End ***

		/*							*** WARNING ***
		 *	Runtime classes must be allocated in either heap or virtual memory(ECSMemory)
		*/

		// *** Runtime Classes Start ***
	public:
		static RuntimeClass* GenerateRuntimeClass(DEFINITON_ID classDefinitionId, void* runtimePtrToClass)
		{
			ClassDefinition* classDefinition = FetchClassDefinition(classDefinitionId);
			RuntimeClass* runtimeClass = new RuntimeClass(runtimePtrToClass, classDefinition);

			RuntimeClasses.push_back(runtimeClass);

			return runtimeClass;
		}

		static RuntimeClass* FetchRuntimeClass() {}

	private:
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

		// *** Runtime Classes End ***
	};
}