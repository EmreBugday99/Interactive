#include <iostream>

#include "ecs/ECSMemory.hpp"
#include "reflection/ClassType.hpp"

class TestClass
{
public:
	int test;

	TestClass()
	{
		std::cout << "I am being created!" << std::endl;
		test = 0;
	}

	TestClass(TestClass& copyClass)
	{
		std::cout << "I am being copied!" << std::endl;
		test = copyClass.test;
	}

	void SayHello()
	{
		std::cout << "Hello Mother Fucker" << std::endl;
	}
};

int main()
{
	using namespace Interactive;

	TestClass testClass = TestClass();
	ClassType<TestClass>::AssignStaticClass(testClass);

	unsigned int i = ECSMemory<TestClass>::Add();
	unsigned int i2 = ECSMemory<TestClass>::Add();

	TestClass* t = ECSMemory<TestClass>::FetchWithMemoryIndex(i);
	TestClass* t2 = ECSMemory<TestClass>::FetchWithMemoryIndex(i2);

	std::cout << "Memory Size: " << ECSMemory<TestClass>::GetMemorySize() << std::endl;

	//ECSMemory<TestClass>::Remove(0);
	//t = SandboxMemory<TestClass>::Fetch(i);

	std::cout << "Memory Size: " << ECSMemory<TestClass>::GetMemorySize() << std::endl;

	t->SayHello();
	t->test = 100;
	std::cout << t << std::endl;
	std::cout << t2 << std::endl;

	return 0;
	//using namespace Interactive::Reflection;
	//using namespace Interactive::ECS;
	//TestClass testClassType = TestClass();
	//ClassType<TestClass>::AssignEmptyClass(testClassType);

	//std::vector<unsigned char> memory;

	//ECSManager ecs = ECSManager();
	//const size_t classIndex1 = ECSManager::CreateComponent<TestClass>(memory);
	//const size_t classIndex2 = ECSManager::CreateComponent<TestClass>(memory);

	//TestClass* testClass = ECSManager::GetComponent<TestClass>(memory, classIndex1);
	//testClass->SayHello();

	////memory.clear();
	//ECSManager::DeleteComponent<TestClass>(memory, classIndex1);

	//testClass = ECSManager::GetComponent<TestClass>(memory, classIndex1);
	//testClass->SayHello();

	//std::cout << ClassType<int>::GetStaticClass() << std::endl;
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