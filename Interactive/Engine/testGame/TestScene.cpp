#include "TestScene.h"
#include "../scene/Scene.h"
#include "../scene/SceneManager.h"
#include "../components/Sprite2D.h"

TestScene::TestScene(Interactive* engine, std::string name): Scene(engine, name)
{
}

void TestScene::OnSceneCreated()
{
	Scene::OnSceneCreated();

	std::cout << "I am constructing entities!" << std::endl;

	Entity* newEntity = CreateNewEntity("New Test Entity");
	Sprite2D* sprite = newEntity->AddComponent<Sprite2D>();

	//Texture* smileyTexture = Engine->TextureSystem->CreateTexture("smiley", "smiley.png");
	//sprite->AttachTexture(smileyTexture);
}

void TestScene::OnSceneEnabled()
{
	Scene::OnSceneEnabled();
}

void TestScene::OnSceneDisabled()
{
	Scene::OnSceneDisabled();
}