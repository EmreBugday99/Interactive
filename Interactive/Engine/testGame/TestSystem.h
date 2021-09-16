#pragma once
#include "../ecs/BaseSystem.h"

namespace Interactive
{
	class TestSystem : public Interactive::BaseSystem
	{
	public:
		void OnUpdate(const float deltaTime) override;
		void OnRender() override;
	};
}