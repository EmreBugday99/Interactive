#pragma once

namespace Interactive
{
	struct BaseSystem
	{
		BaseSystem();

		virtual void OnUpdate(const float deltaTime);
		virtual void OnRender();
	};
}