#pragma once
#include <map>
#include <string>
#include <vector>

class Interactive;
class Entity;
class EntityManager
{
public:
	Interactive* Engine;

	~EntityManager();

	Entity* CreateEntity(std::string entityName);
	Entity* GetEntityByName(std::string entityName);

	void JoinEntitiesIntoGameLoop();
	void RemoveEntitiesFromGameLoop();

private:
	friend class Interactive;
	friend class Entity;

	/// <summary>
	/// Entities that are waiting to be initialized and enter game loop.
	/// </summary>
	std::vector<Entity*> EntitiesWaitingToJoin;
	/// <summary>
	/// Entities that are currently in the game loop.
	/// </summary>
	std::vector<Entity*> EntitiesInGameLoop;
	/// <summary>
	/// Entities that are waiting to be destroyed and leave the game loop.
	/// </summary>
	std::vector<Entity*> EntitiesWaitingToLeave;

	size_t EntityCount;
	size_t MaxEntityCount;

	EntityManager(Interactive* engine);
};
