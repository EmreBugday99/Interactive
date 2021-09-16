#include "TestSystem.h"

#include "TestComponent.hpp"
#include "TestComponent2.hpp"
#include "../ecs/ECSManager.h"

void TestSystem::OnUpdate(const float deltaTime)
{
	using namespace Interactive;

	BaseSystem::OnUpdate(deltaTime);

	const unsigned int entityCount = ECSMemory<Entity2>::GetSliceCount();
	for (unsigned int i = 0; i < entityCount; i++)
	{
		Entity2* entity = ECSMemory<Entity2>::FetchWithSliceIndex(i);

		TestComponent* testComp = ECSManager::GetComponentFromEntity<TestComponent>(entity->EntityId);
		TestComponent2* testComp2 = ECSManager::GetComponentFromEntity<TestComponent2>(entity->EntityId);

		if (testComp == nullptr && testComp2 == nullptr)
			continue;

		testComp->TestInt += 100;

		std::cout << "[Test System] [Test Comp] [TestInt]: " << testComp->TestInt << std::endl;
	}
}

void TestSystem::OnRender()
{
	BaseSystem::OnRender();
}