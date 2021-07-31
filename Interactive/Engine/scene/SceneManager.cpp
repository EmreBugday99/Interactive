#include "../includes/CoreIncludes.h"

SceneManager::SceneManager(Interactive* engine)
{
}

SceneManager::~SceneManager()
{
	for (size_t i = Scenes.size() - 1; i > 0; --i)
	{
		delete(Scenes[i]);
		Scenes[i] = nullptr;
	}
}

Scene* SceneManager::LoadScene(const char* scenePath)
{

	
	return nullptr;
}

Scene* SceneManager::CreateEmptyScene(const char* sceneName)
{
	Scene* scene = new Scene();
	scene->SceneName = sceneName;
	
	return nullptr;
}

void SceneManager::SetActiveScene(Scene* scene)
{
}