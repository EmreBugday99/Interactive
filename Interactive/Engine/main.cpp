#include <fstream>
#include "includes/CoreIncludes.h"
#include "scene/SceneManager.h"
#include "testGame/TestScene.h"

int main()
{
	Interactive* engine = new Interactive("Test Game Window");

	TestScene* testScene = engine->SceneSystem->CreateCustomScene<TestScene>(engine, "Test Scene");
	engine->SceneSystem->SetActiveScene(testScene);

	engine->Start();

	delete(engine);
	return 0;
}
