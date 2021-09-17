#pragma once

#include <vector>
#include "../ecs/ECSReturn.hpp"
#include "../ecs/ECSMemory.hpp"
#include "../debugging/ErrorHandler.hpp"
#include "../reflection/ClassType.hpp"

namespace Interactive
{
	struct Entity2;
	struct BaseSystem;

	class ECSManager
	{
	public:
		static void Initialize();

		static ECSReturn CreateEntity();

		static Entity2* GetEntity(const unsigned int entityId);

		template<typename T>
		static ECSReturn CreateComponent(const unsigned int entityId)
		{
			ECSReturn ecsReturn = ECSReturn();
			ecsReturn.ReturnIndex = 0;
			ecsReturn.SuccessfulReturn = false;

			T* existingComponent = GetComponentFromEntity<T>(entityId);
			if (existingComponent != nullptr)
			{
				ErrorHandler::OnError("Component already exists on entity!");
				return ecsReturn;
			}

			const unsigned int memoryIndex = ECSMemory<T>::Add();
			T* newComponent = ECSMemory<T>::FetchWithMemoryIndex(memoryIndex);

			newComponent->TypeId = ClassType<T>::TypeId;
			newComponent->ComponentId = memoryIndex;
			newComponent->OwnerId = entityId;

			ecsReturn.ReturnIndex = memoryIndex;
			ecsReturn.SuccessfulReturn = true;

			return ecsReturn;
		}

		template<typename T>
		static T* GetComponentFromEntity(const unsigned int entityId)
		{
			for (unsigned int i = 0; i < ECSMemory<T>::GetSliceCount(); i++)
			{
				const unsigned int componentOwnerId = ECSMemory<T>::FetchWithSliceIndex(i)->OwnerId;

				if (componentOwnerId == entityId)
					return ECSMemory<T>::FetchWithSliceIndex(i);
			}

			return nullptr;
		}

		static void AddSystem(BaseSystem* system);

		static void Update();

		static void OnEntityRemoved(const std::string& memoryAlias, void* data);

	private:
		inline static std::vector<BaseSystem*> Systems;
	};
}