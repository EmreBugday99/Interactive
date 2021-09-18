#pragma once
#include "../ecs/BaseSystem.h"

namespace Interactive
{
	class TestSystem2 : public Interactive::BaseSystem
	{
	public:
		TestSystem2();

		bool deleted;

		void OnUpdate(const float deltaTime) override;
		void OnRender() override;
	};
}
