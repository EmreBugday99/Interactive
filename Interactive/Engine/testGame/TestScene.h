#pragma once
#include "../scene/Scene.h"

class Component;

class TestScene : public Scene
{
	friend class SceneManager;
	TestScene(Interactive* engine, std::string name);

protected:
	void OnSceneCreated() override;
	void OnSceneEnabled() override;
	void OnSceneDisabled() override;

	void PrintComponentSize(Component* component);
};
