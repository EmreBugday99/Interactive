#include <fstream>

#include "includes/CoreIncludes.h"

int main()
{
	Interactive* engine = new Interactive("Test Game Window");

	Entity* cameraEntity = engine->ECManager->CreateEntity("Camera Entity", engine->SceneSystem->ActiveScene);
	Camera* cameraComp = cameraEntity->AddComponent<Camera>();
	engine->MainCamera = cameraComp;

	//std::vector<std::string> comps = { "assets/scripts/testComponent.lua", "assets/scripts/testComponent.lua" };
	//engine->AssetSystem->CreateEntityAsset("assetTestEntity", glm::vec3(0.0f, 0.0f, 0.0f), comps);
	
	engine->Start();

	delete(engine);
	return 0;
}