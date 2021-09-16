#include "TestSystem2.h"

#include <iostream>

#include "TestComponent3.hpp"
#include "../ecs/ECSMemory.hpp"

void Interactive::TestSystem2::OnUpdate(const float deltaTime)
{
	BaseSystem::OnUpdate(deltaTime);

	unsigned int componentCount = ECSMemory<TestComponent3>::GetSliceCount();

	for (unsigned int i = 0; i < componentCount; i++)
	{
		TestComponent3* component = ECSMemory<TestComponent3>::FetchWithSliceIndex(i);
		component->TestULongLong += 1;

		std::cout << "[Test System2] [Test Comp 3] [TestULongLong]: " << i << " " << component->TestULongLong << std::endl;
	}
}

void Interactive::TestSystem2::OnRender()
{
	BaseSystem::OnRender();
}