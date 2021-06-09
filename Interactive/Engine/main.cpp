#include <iostream>
#include "TestComponent.h"
#include "includes/CoreIncludes.h"

int main()
{
	Interactive* engine = new Interactive("Test Game Window");

	Entity* cameraEntity = engine->ECManager->CreateEntity("Camera Entity");
	Camera* cameraComp = cameraEntity->AddComponent<Camera>();
	engine->MainCamera = cameraComp;

	Entity* testEntity = engine->ECManager->CreateEntity("Test Entity");
	testEntity->AddComponent<TestComponent>();

	engine->Start();

	delete(engine);
	return 0;
}