#include "TestScene.h"

#include "GameSprite.h"
#include "../scene/Scene.h"
#include "../components/Sprite2D.h"

TestScene::TestScene(Interactive* engine, std::string name): Scene(engine, name)
{
}

void TestScene::OnSceneCreated()
{
	Scene::OnSceneCreated();

	std::cout << "I am constructing entities!" << std::endl;

	Entity* cameraEntity = CreateNewEntity("Camera");
	Camera* cameraComp = cameraEntity->AddComponent<Camera>();
	Engine->MainCamera = cameraComp;

	Entity* newEntity = CreateNewEntity("New Test Entity");
	GameSprite* sprite = newEntity->AddComponent<GameSprite>();

	PrintComponentSize(cameraComp);
	PrintComponentSize(sprite);

	//Texture* smileyTexture = Engine->TextureSystem->CreateTexture("smiley", "smiley.jpg");
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

void TestScene::PrintComponentSize(Component* component)
{
	std::cout << "Size Of " << component->Reflection.GetTypeName() << ": " << sizeof(*component) << std::endl;
}
