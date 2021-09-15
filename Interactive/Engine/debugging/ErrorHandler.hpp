#pragma once
#include <iostream>

namespace Interactive
{
	struct ErrorHandler
	{
		inline static void OnError(const char* errorMsg)
		{
			std::cout << errorMsg << std::endl;
		}
	};
}