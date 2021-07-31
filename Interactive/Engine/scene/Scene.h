#pragma once
#include <vector>
#include "../reflection-system/ClassReflection.hpp"

class Entity;
class Interactive;

struct Scene
{
	Interactive* Engine;
	const char* SceneName;
	const char* ScenePath;
	bool IsInitialized;
	std::vector<Entity*> EntitiesInScene;

	ClassReflection Reflection;

private:
	friend class SceneManager;
	Scene();
};

