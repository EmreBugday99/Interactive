#include <iostream>

#include "ecs/ECSManager.hpp"
#include "reflection/ClassType.hpp"

int main()
{
	using namespace Interactive::Reflection;
	ClassType<int> reflection;
	int as = 1234;
	ClassType<int>::AssignEmptyClass(as);
	ClassType<int> reflection2;
	ClassType<double> reflection3;

	std::cout << ClassType<int>::GetStaticClass() << std::endl;
	//std::cout << reflection2.ClassName << std::endl;
	//std::cout << reflection3.ClassName << std::endl;

	return 0;
	//Interactive* engine = new Interactive("Test Game Window");

	//TestScene* testScene = engine->SceneSystem->CreateCustomScene<TestScene>(engine, "Test Scene");
	//engine->SceneSystem->SetActiveScene(testScene);

	//engine->Start();

	//delete(engine);
	//return 0;
}