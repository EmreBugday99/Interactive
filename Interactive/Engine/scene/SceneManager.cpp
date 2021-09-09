#include "SceneManager.h"
#include "Scene.h"
#include "../Interactive.h"
#include "../entity-component/EntityManager.h"

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
	scene->SceneName = sceneName;

	Scenes.push_back(scene);

	scene->OnSceneCreated();

	return nullptr;
}

void SceneManager::SetActiveScene(Scene* scene)
{
	ActiveScene = scene;
}