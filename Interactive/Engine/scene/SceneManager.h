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
	void SetActiveScene(Scene* scene);
	Entity* CreateEntity(const char* entityName);
};
