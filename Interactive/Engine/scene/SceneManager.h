#pragma once
#include <vector>

class Interactive;
struct Scene;
class SceneManager
{
	Interactive* Engine;
	Scene* ActiveScene;
	std::vector<Scene*> Scenes;

public:
	SceneManager(Interactive* engine);
	~SceneManager();
	
	Scene* LoadScene(const char* scenePath);
	Scene* CreateEmptyScene(const char* sceneName);
	void SetActiveScene(Scene* scene);
};
