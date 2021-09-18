#pragma once

namespace Interactive
{
	// [Runtime]
	class RuntimeClass
	{
		//TODO: MAKE THIS ACCESS MODIFIER PRIVATE AFTER DEBUGGING IS OVER
	public:

		friend class RuntimeReflection;

		// Called right before pointer change. Old ptr can be assumed to be still valid.
		typedef void (*ClassUpdateFunc) (RuntimeClass*, RuntimeClass*);
		// Called right before a class get destructed. Pointer can still be assumed to be valid.
		typedef void (*ClassDestroyFunc) (RuntimeClass*);

		// Called right before pointer change. Old ptr can be assumed to be still valid.
		inline static std::vector<ClassUpdateFunc> ClassPtrChangeObservers;

		// Called right before a class get destructed. Pointer can still be assumed to be valid.
		inline static std::vector<ClassDestroyFunc> ClassDestroyObservers;

		// [Data]
		void* ClassPtr;
		ClassDefinition* Definition;

		RuntimeClass(void* classPtr, ClassDefinition* classDefinition)
			: ClassPtr(classPtr), Definition(classDefinition) {}

		~RuntimeClass()
		{
			if (ClassDestroyObservers.empty() == false)
			{
				for (ClassDestroyFunc destroyFunc : ClassDestroyObservers)
				{
					destroyFunc(this);
				}
			}
		}

	public:
		//TODO: All the getters will be here
	};
}