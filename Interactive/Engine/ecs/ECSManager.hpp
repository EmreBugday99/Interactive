#pragma once

#include "ECSMemory.hpp"
#include "Entity.hpp"
#include "../debugging/ErrorHandler.hpp"

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
		static T* CreateComponent(Interactive::Entity* entity)
		{
			if (entity->ComponentMap.empty() == false)
			{
				auto search = entity->ComponentMap.find(ClassType<T>::TypeId);
				if (search != entity->ComponentMap.end())
				{
					ErrorHandler::OnError("Can't add component! Entity already contains that component.");
					return nullptr;
				}
			}

			const unsigned int memoryIndex = ECSMemory<T>::Add();
			T* component = ECSMemory<T>::FetchWithMemoryIndex(memoryIndex);

			component->TypeId = ClassType<T>::TypeId;
			component->ComponentId = memoryIndex;
			component->Entity = entity;
			entity->ComponentMap[ClassType<T>::TypeId] = component;
			entity->ComponentMap.insert({ ClassType<T>::TypeId, component });

			return component;
		}

		template<typename T>
		static T* FetchComponentFromEntity(Entity* entity)
		{
			auto search = entity->ComponentMap.find(ClassType<T>::TypeId);
			if (search == entity->ComponentMap.end())
			{
				ErrorHandler::OnError("Fetch failed nullptr");
				return nullptr;
			}

			return (T*)search->second;
		}

	private:
		static void Update()
		{
			/*
			 * for(entity* : all entities)
			 * {
			 *		for(types : entity.compTypes)
			 *		{
			 *			if(type == ClassType<Transform>::TypeId)
			 *			{
			 *
			 *			}
			 *		}
			 *
			 *
			 *		Transform* transform = ECSManager::FetchComponent<Transform>(entity);
			 *					=> ECSMemory<Transform>
			 *						-> for(Transform* : ECSMemory<Transform>)
			 *							-> if(Transform->Entity == entity)
			 *								return Transform*;
			 *
			 *		Transform.DoShit();
			 * }
			 *
			 * T* FetchCompomemt<T>(entity*)
			 * {
			 *
			 *	return entity.ComponentMap[ClassType<T>::TypeId]
			 *
			 * }
			 */
		}
	};
}