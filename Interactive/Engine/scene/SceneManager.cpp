#include "SceneManager.h"
#include "Scene.h"
#include "../Interactive.h"

SceneManager::SceneManager(Interactive* engine)
{
	Engine = engine;
}

SceneManager::~SceneManager()
{
	for (size_t i = Scenes.size() - 1; i > 0; --i)
	{
		delete(Scenes[i]);
		Scenes[i] = nullptr;
	}
}

Scene* SceneManager::CreateEmptyScene(std::string sceneName)
{
	Scene* scene = new Scene(Engine, sceneName);
	//scene->SceneName = sceneName;

	//Scenes.push_back(scene);

	return nullptr;
}

void SceneManager::SetActiveScene(Scene* scene)
{
	ActiveScene = scene;
}

Entity* SceneManager::CreateEntity(const char* entityName)
{
	Entity* newEntity = Engine->ECManager->CreateEntity(entityName, ActiveScene);
	ActiveScene->EntitiesInScene.push_back(newEntity);

	return newEntity;
}