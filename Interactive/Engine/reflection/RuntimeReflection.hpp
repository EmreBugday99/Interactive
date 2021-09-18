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
		inline static DEFINITION_SIZE DefinitionCounter;

	public:

		static void Initialize()
		{
			RuntimeClass::ClassPtrChangeObservers.push_back(BeforeRuntimeClassPtrChange);
			RuntimeClass::ClassDestroyObservers.push_back(BeforeRuntimeClassDestroy);
		}

		static DEFINITION_ID GenerateClassDefinition(std::string className, DEFINITION_SIZE classSize)
		{
			const std::string typeName = GetClassName(className);
			// bool = brand new definition | DEFINITION_ID = pretty self explanatory...
			const std::pair<bool, DEFINITION_ID> definitionPair = GenerateClassDefinitionId(typeName);

			// If a class definition already exists for a certain type we return the existing definition id for the type.
			if (definitionPair.first == true)
				return definitionPair.second;

			const auto classType = new ClassDefinition(typeName, definitionPair.second, classSize);
			ClassDefinitions.push_back(classType);

			return definitionPair.second;
		}

		static ClassDefinition* FetchClassDefinition(DEFINITION_ID classId)
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

		static std::pair<bool, DEFINITION_ID> GenerateClassDefinitionId(std::string className)
		{
			ClassDefinition* existingDefinition = nullptr;

			for (ClassDefinition* definition : ClassDefinitions)
			{
				if (className == definition->DefinitionName)
				{
					std::cout << "kjhasahkjdas";
					existingDefinition = definition;
				}
			}

			if (existingDefinition == nullptr)
			{
				bool newDef = false;
				DEFINITION_ID id = DefinitionCounter++;

				return std::make_pair(newDef, id);
			}

			return std::make_pair(true, existingDefinition->DefinitionId);
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
		static RuntimeClass* GenerateRuntimeClass(DEFINITION_ID classDefinitionId, void* runtimePtrToClass)
		{
			ClassDefinition* classDefinition = FetchClassDefinition(classDefinitionId);
			RuntimeClass* runtimeClass = new RuntimeClass(runtimePtrToClass, classDefinition);

			RuntimeClasses.push_back(runtimeClass);

			return runtimeClass;
		}

		static char FetchAllRuntimeClassesOfDefinition(std::vector<RuntimeClass*>& vectorToFill, DEFINITION_ID definitionId)
		{
			bool foundAnyDefinitionMatch = false;

			for (RuntimeClass* runtimeClass : RuntimeClasses)
			{
				if (definitionId == runtimeClass->Definition->DefinitionId)
				{
					vectorToFill.push_back(runtimeClass);
					foundAnyDefinitionMatch = true;
				}
			}

			if (!foundAnyDefinitionMatch)
				return -1;
			return 1;
		}

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

		static void BeforeRuntimeClassDestroy(RuntimeClass* runtimePtr)
		{
			unsigned int index = 0;

			for (RuntimeClass* runtimeClass : RuntimeClasses)
			{
				if (runtimePtr == runtimeClass)
					break;

				index++;
			}

			std::cout << "Deleting: " << RuntimeClasses[index]->Definition->DefinitionName << std::endl;

			RuntimeClasses.erase(RuntimeClasses.begin() + index);
		}

		// *** Runtime Classes End ***
	};
}