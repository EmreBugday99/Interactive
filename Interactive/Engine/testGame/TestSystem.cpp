#include "TestSystem.h"

#include "TestComponent.hpp"
#include "TestComponent2.hpp"
#include "../ecs/ECSManager.h"
#include "../ecs/Entity.hpp"

void Interactive::TestSystem::OnUpdate(const float deltaTime)
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

		testComp->TestInt += 1;

		std::cout << "[Test System] [Test Comp] [TestInt]: " << i << " " << testComp->TestInt << std::endl;
	}
}

void Interactive::TestSystem::OnRender()
{
	BaseSystem::OnRender();
}