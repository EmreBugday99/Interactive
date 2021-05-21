#pragma once
#include <string>
#include <vector>

class Interactive;
class Entity;
class EntityManager
{
public:
	Interactive* Engine;
	std::vector<Entity*> Entities;

	~EntityManager();

	Entity* CreateEntity(std::string entityName);
	Entity* GetEntityByName(std::string entityName);

private:
	friend class Interactive;
	EntityManager(Interactive* engine);
};
