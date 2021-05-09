#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager(InteractiveEngine* engine) : Engine(engine){}

EntityManager::~EntityManager()
{
	DestroyAllEntities();
}

Entity* EntityManager::CreateEntity(std::string entityName)
{
	Entity* newEntity = new Entity(entityName);
	newEntity->Engine = Engine;
	Entities.push_back(newEntity);

	return newEntity;
}

Entity* EntityManager::GetEntityByName(std::string entityName)
{
	for (Entity*& entity : Entities)
	{
		if (entity->EntityName == entityName)
			return entity;
	}

	return nullptr;
}

void EntityManager::DestroyAllEntities()
{
}