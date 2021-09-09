#include "Scene.h"
#include "../entity-component/EntityManager.h"

Entity* Scene::CreateNewEntity(std::string entityName)
{
	Entity* newEntity = Engine->ECManager->CreateEntity(entityName, this);

	return newEntity;
}

void Scene::OnSceneCreated() {}

void Scene::OnSceneEnabled() {}

void Scene::OnSceneDisabled() {}