#pragma once
#include "../ecs/BaseSystem.h"

namespace Interactive
{
	class TestSystem : public Interactive::BaseSystem
	{
	public:
		TestSystem();

		bool deleted;
		void OnUpdate(const float deltaTime) override;
		void OnRender() override;
	};
}