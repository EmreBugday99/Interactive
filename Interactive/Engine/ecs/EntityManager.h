#pragma once
#include <string>
#include <vector>

class Entity;
class EntityManager
{
public:
	std::vector<Entity*> Entities;

	EntityManager();
	~EntityManager();

	Entity* CreateEntity(std::string entityName);
	Entity* GetEntityByName(std::string entityName);
	void DestroyAllEntities();
};
