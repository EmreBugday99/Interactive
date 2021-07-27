#include <iostream>
#include "TestComponent.h"
#include "TestComponent2.h"
#include "includes/CoreIncludes.h"

int main()
{
	Interactive* engine = new Interactive("Test Game Window");

	Entity* cameraEntity = engine->ECManager->CreateEntity("Camera Entity");
	Camera* cameraComp = cameraEntity->AddComponent<Camera>();
	engine->MainCamera = cameraComp;

	Entity* testEntity = engine->ECManager->CreateEntity("Test Entity");
	testEntity->AddComponent<Sprite2D>();
	testEntity->AddComponent<TestComponent>();

	Entity* testEntity2 = engine->ECManager->CreateEntity("Test Entity 2");
	testEntity2->AddComponent<TestComponent2>();

	engine->Start();

	delete(engine);
	return 0;
}