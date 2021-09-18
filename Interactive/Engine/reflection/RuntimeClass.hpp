#pragma once

namespace Interactive
{
	class RuntimeClass
	{
		friend class RuntimeReflection;

		typedef void (*ClassUpdateFunc) (RuntimeClass*, RuntimeClass*);
		// Called right before pointer change. Old ptr can be assumed to be still valid.
		inline static std::vector<ClassUpdateFunc> ClassPtrChangeObservers;

		void* ClassPtr;
		ClassDefinition* ClassType;

		RuntimeClass(void* classPtr, ClassDefinition* classDefinition)
			: ClassPtr(classPtr), ClassType(classDefinition)
		{}

	public:
		//TODO: All the getters will be here
	};
}