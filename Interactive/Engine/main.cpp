#include <iostream>
#include "includes/CoreIncludes.h"
#include <functional>

int main()
{
	Interactive* engine = new Interactive("Test Game Window");

	Entity* cameraEntity = engine->ECManager->CreateEntity("Camera Entity");
	Camera* cameraComp = cameraEntity->AddComponent<Camera>();
	engine->MainCamera = cameraComp;
	
	engine->Start();

	delete(engine);
	return 0;
}
