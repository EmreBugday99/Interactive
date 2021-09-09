#pragma once
#include <vector>
#include "../reflection-system/ClassReflection.hpp"
#include "../Interactive.h"
#include "../entity-component/EntityManager.h"

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

private:
	friend class SceneManager;
	Scene(Interactive* engine, std::string sceneName)
	{
		SceneName = sceneName;
		Engine = engine;
		IsInitialized = false;
	}
};