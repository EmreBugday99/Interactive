#pragma once
#include <string>
#include <vector>

class Entity;
class Interactive;
struct Scene;
class SceneManager
{
	Interactive* Engine;

public:
	std::vector<Scene*> Scenes;
	SceneManager(Interactive* engine);
	~SceneManager();

	Scene* ActiveScene;

	//TODO: Finish this bad boi
	//Scene* LoadScene(const char* scenePath);
	Scene* CreateEmptyScene(std::string sceneName);

	template<typename T, typename... TArgs>
	T* CreateCustomScene(TArgs... args)
	{
		T* newScene = new T(std::forward<TArgs>(args)...);

		Scenes.push_back(newScene);


		newScene->OnSceneCreated();
		return newScene;
	}

	void SetActiveScene(Scene* scene);
};
