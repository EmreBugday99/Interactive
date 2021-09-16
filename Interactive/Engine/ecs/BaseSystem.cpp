#include "BaseSystem.h"

#include "ECSManager.h"

namespace Interactive
{
	Interactive::BaseSystem::BaseSystem()
	{
		ECSManager::AddSystem(this);
	}

	void BaseSystem::OnUpdate(const float deltaTime) {}

	void BaseSystem::OnRender() {}
}