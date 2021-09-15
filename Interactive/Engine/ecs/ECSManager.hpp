#pragma once

#include "ECSMemory.hpp"
#include "Entity.hpp"

namespace Interactive
{
	class ECSManager
	{
	public:
		static Entity* CreateEntity()
		{
			const unsigned int memoryIndex = ECSMemory<Entity>::Add();
			Entity* entity = ECSMemory<Entity>::FetchWithMemoryIndex(memoryIndex);
			entity->EntityId = memoryIndex;

			return entity;
		}

		template<typename T>
		inline static T* CreateComponent(Entity* entity)
		{
			const unsigned int memoryIndex = ECSMemory<T>::Add();
			T* component = ECSMemory<T>::FetchWithMemoryIndex(memoryIndex);

			component->TypeId = ClassType<T>::TypeId;
			component->ComponentId = memoryIndex;
			component->Entity = entity;

			entity->ComponentTypes.emplace_back(ClassType<T>::TypeId);

			return component;
		}

	private:
		static void Update()
		{
		}
	};
}