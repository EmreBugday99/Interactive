#include "TestSystem2.h"

#include <iostream>

#include "TestComponent3.hpp"
#include "../ecs/ECSMemory.hpp"

Interactive::TestSystem2::TestSystem2() : deleted(false)
{
}

void Interactive::TestSystem2::OnUpdate(const float deltaTime)
{
	BaseSystem::OnUpdate(deltaTime);

	unsigned int componentCount = ECSMemory<TestComponent3>::GetSliceCount();

	bool deleteFirstComponent = false;
	for (unsigned int i = 0; i < componentCount; i++)
	{
		TestComponent3* component = ECSMemory<TestComponent3>::FetchWithSliceIndex(i);
		component->TestULongLong += 1;
		if (component->TestULongLong > 1000)
		{
			deleteFirstComponent = true;
		}

		std::cout << "[Test System2] [Test Comp 3] [TestULongLong]: " << i << " " << component->TestULongLong << std::endl;
	}

	if (deleteFirstComponent && !deleted)
	{
		deleted = true;
		ECSMemory<Entity2>::Remove(0);
	}
}

void Interactive::TestSystem2::OnRender()
{
	BaseSystem::OnRender();
}