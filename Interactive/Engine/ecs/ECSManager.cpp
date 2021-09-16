#include "ECSManager.h"

#include "BaseSystem.h"
#include "ECSMemory.hpp"
#include "Entity.hpp"

namespace Interactive
{
	ECSReturn ECSManager::CreateEntity()
	{
		ECSReturn ecsReturn = ECSReturn();

		const unsigned int memoryIndex = ECSMemory<Entity2>::Add();
		Entity2* entity = ECSMemory<Entity2>::FetchWithMemoryIndex(memoryIndex);
		entity->EntityId = memoryIndex;

		ecsReturn.ReturnIndex = memoryIndex;
		ecsReturn.SuccessfulReturn = true;

		return ecsReturn;
	}

	Entity2* ECSManager::GetEntity(const unsigned entityId)
	{
		return ECSMemory<Entity2>::FetchWithMemoryIndex(entityId);
	}

	void ECSManager::AddSystem(BaseSystem* system)
	{
		Systems.push_back(system);
	}

	void ECSManager::Update()
	{
		for (BaseSystem* system : Systems)
		{
			system->OnUpdate(1.0f);
		}
		for (BaseSystem* system : Systems)
		{
			system->OnRender();
		}
	}
}