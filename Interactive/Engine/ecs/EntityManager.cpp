#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager(Interactive* engine) : Engine(engine), EntityCount(0), MaxEntityCount(0) {}
EntityManager::~EntityManager() {}

Entity* EntityManager::CreateEntity(std::string entityName)
{
	Entity* newEntity = new Entity(entityName, Engine);
	EntitiesWaitingToJoin.push_back(newEntity);

	return newEntity;
}

Entity* EntityManager::GetEntityByName(std::string entityName)
{
	for (Entity* entity : EntitiesInGameLoop)
	{
		if (entity->EntityName == entityName)
			return entity;
	}

	return nullptr;
}

void EntityManager::JoinEntitiesIntoGameLoop()
{
	size_t entityIndex = EntitiesWaitingToJoin.size();
	while (entityIndex)
	{
		entityIndex--;
		Entity* entityToJoin = EntitiesWaitingToJoin[entityIndex];

		EntitiesInGameLoop.push_back(entityToJoin);
	}

	EntitiesWaitingToJoin.clear();
}

void EntityManager::RemoveEntitiesFromGameLoop()
{
	size_t entityIndex = EntitiesWaitingToLeave.size();
	while (entityIndex)
	{
		entityIndex--;
		Entity* entityToLeave = EntitiesWaitingToLeave[entityIndex];

		size_t secondEntityIndex = EntitiesInGameLoop.size();
		while (secondEntityIndex)
		{
			secondEntityIndex--;
			Entity* entityToCompareAgainst = EntitiesInGameLoop[secondEntityIndex];

			if (entityToLeave == entityToCompareAgainst)
				EntitiesInGameLoop.erase(EntitiesInGameLoop.begin() + secondEntityIndex);
		}
	}

	EntitiesWaitingToLeave.clear();
}