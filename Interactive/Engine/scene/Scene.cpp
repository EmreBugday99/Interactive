#include "Scene.h"

namespace IE {
	Scene::Scene()
	{
		entt::entity entity = Registry.create();
	}

	Scene::~Scene()
	{
		Registry.clear();
	}

	entt::entity Scene::CreateEntity()
	{
		return Registry.create();
	}

}