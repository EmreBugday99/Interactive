#include "ecs/ECSManager.h"
#include "testGame/TestComponent.hpp"
#include "testGame/TestComponent2.hpp"
#include "testGame/TestComponent3.hpp"
#include "testGame/TestSystem.h"
#include "testGame/TestSystem2.h"

int main()
{
	const auto ecsReturnEntity = Interactive::ECSManager::CreateEntity();
	const auto ecsReturnEntity2 = Interactive::ECSManager::CreateEntity();

	Interactive::ECSManager::CreateComponent<TestComponent>(ecsReturnEntity.ReturnIndex);
	Interactive::ECSManager::CreateComponent<TestComponent2>(ecsReturnEntity.ReturnIndex);
	Interactive::ECSManager::CreateComponent<TestComponent>(ecsReturnEntity2.ReturnIndex);
	Interactive::ECSManager::CreateComponent<TestComponent2>(ecsReturnEntity2.ReturnIndex);

	Interactive::ECSMemory<TestComponent3>::Add();

	Interactive::TestSystem* testSystem = new Interactive::TestSystem();
	Interactive::TestSystem2* testSystem2 = new Interactive::TestSystem2();

	Interactive::ECSManager::AddSystem(testSystem);
	Interactive::ECSManager::AddSystem(testSystem2);

	while (true)
	{
		Interactive::ECSManager::Update();
	}

	return 0;
}