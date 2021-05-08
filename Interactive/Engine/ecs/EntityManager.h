#pragma once
#include <string>
#include <vector>

class InteractiveEngine;
class Entity;
class EntityManager
{
public:
	InteractiveEngine* Engine;
	std::vector<Entity*> Entities;

	EntityManager();
	~EntityManager();

	Entity* CreateEntity(std::string entityName);
	Entity* GetEntityByName(std::string entityName);
	void DestroyAllEntities();
};
