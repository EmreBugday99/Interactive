#include "EntityManager.h"
#include "Entity.h"
#include "../scene/SceneManager.h"
#include "../scene/Scene.h"

EntityManager::EntityManager(Interactive* engine) : Engine(engine) {}
EntityManager::~EntityManager() {}

Entity* EntityManager::CreateEntity(std::string entityName, Scene* scene)
{
	Entity* newEntity = new Entity(entityName, Engine, false);
	EntitiesWaitingToJoin.push_back(newEntity);

	return newEntity;
}

Entity* EntityManager::GetEntityByName(std::string entityName)
{
	for (Entity* entity : Engine->SceneSystem->ActiveScene->EntitiesInScene)
	{
		if (entity->EntityName == entityName)
			return entity;
	}

	for (Entity* entity : EntitiesWaitingToJoin)
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

		//EntitiesInGameLoop.push_back(entityToJoin);

		Engine->SceneSystem->ActiveScene->EntitiesInScene.push_back(entityToJoin);

		EntitiesWaitingToJoin.erase(EntitiesWaitingToJoin.begin() + entityIndex);
	}
}

void EntityManager::RemoveEntitiesFromGameLoop()
{
	size_t entityIndex = EntitiesWaitingToLeave.size();
	while (entityIndex)
	{
		entityIndex--;
		Entity* entityToLeave = EntitiesWaitingToLeave[entityIndex];

		size_t secondEntityIndex = Engine->SceneSystem->ActiveScene->EntitiesInScene.size();
		while (secondEntityIndex)
		{
			secondEntityIndex--;
			Entity* entityToCompareAgainst = Engine->SceneSystem->ActiveScene->EntitiesInScene[secondEntityIndex];

			if (entityToLeave == entityToCompareAgainst)
			{
				Engine->SceneSystem->ActiveScene->EntitiesInScene.erase(
					Engine->SceneSystem->ActiveScene->EntitiesInScene.begin() + secondEntityIndex);
			}
		}
		EntitiesWaitingToLeave.erase(EntitiesWaitingToLeave.begin() + entityIndex);
	}
}