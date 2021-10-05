#pragma once
#include <vector>

namespace IE
{
	class SystemManager
	{
	public:
		using UpdateCallback = void(*) (float deltaTime);
		using RenderCallback = void(*) ();

		inline static std::vector<UpdateCallback()> UpdateCallbacks;
		inline static std::vector<RenderCallback()> RenderCallbacks;
	};
}