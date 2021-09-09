#pragma once
#include <vector>
#include "../Interactive.h"

class Entity;
class Interactive;

struct Scene
{
	Interactive* Engine;
	std::string SceneName;
	//const char* ScenePath;
	bool IsInitialized;
	std::vector<Entity*> EntitiesInScene;

	void AddExistingEntityToScene(Entity* entity) { EntitiesInScene.push_back(entity); }
	Entity* CreateNewEntity(std::string entityName);

protected:
	friend class SceneManager;
	//TODO: Find a better name for the functions
	virtual void OnSceneCreated();
	virtual void OnSceneEnabled();
	virtual void OnSceneDisabled();

protected:
	friend class SceneManager;
	Scene(Interactive* engine, std::string sceneName)
	{
		SceneName = sceneName;
		Engine = engine;
		IsInitialized = false;
	}
};