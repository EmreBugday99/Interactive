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

	~EntityManager();

	Entity* CreateEntity(std::string entityName);
	Entity* GetEntityByName(std::string entityName);

private:
	friend class InteractiveEngine;
	EntityManager(InteractiveEngine* engine);
};
