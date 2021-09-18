#include "ecs/ECSManager.h"
#include "testGame/TestComponent.hpp"
#include "testGame/TestComponent2.hpp"
#include "testGame/TestComponent3.hpp"
#include "testGame/TestSystem.h"
#include "testGame/TestSystem2.h"
#include <source_location>

void TestSourceLoc(int i)
{
	const std::source_location& srcLoc = std::source_location::current();
	std::cout << "Function: " << srcLoc.function_name() << std::endl;
}

int main()
{
	using namespace  Interactive;

	TestSourceLoc(123);

	//std::string className = RuntimeReflection::GET_CLASS_NAME;

	//std::cout << className << std::endl;

	return 0;

	ECSMemory<Entity2>::InitializeMemory();
	ECSMemory<Entity2>::SetAlias("Entity");

	ECSMemory<TestComponent>::InitializeMemory();
	ECSMemory<TestComponent>::SetAlias("TestComponent");

	ECSMemory<TestComponent2>::InitializeMemory();
	ECSMemory<TestComponent2>::SetAlias("TestComponent2");

	ECSMemory<TestComponent3>::InitializeMemory();
	ECSMemory<TestComponent3>::SetAlias("TestComponent3");

	const auto ecsReturnEntity = ECSManager::CreateEntity();
	const auto ecsReturnEntity2 = ECSManager::CreateEntity();

	ECSManager::CreateComponent<TestComponent>(ecsReturnEntity.ReturnIndex);
	ECSManager::CreateComponent<TestComponent2>(ecsReturnEntity.ReturnIndex);
	ECSManager::CreateComponent<TestComponent>(ecsReturnEntity2.ReturnIndex);
	ECSManager::CreateComponent<TestComponent2>(ecsReturnEntity2.ReturnIndex);

	ECSMemory<TestComponent3>::Add();
	ECSMemory<TestComponent3>::Add();

	TestSystem* testSystem = new TestSystem();
	TestSystem2* testSystem2 = new TestSystem2();

	ECSManager::AddSystem(testSystem);
	ECSManager::AddSystem(testSystem2);

	while (true)
	{
		ECSManager::Update();
	}

	return 0;
}