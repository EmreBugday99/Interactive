#pragma once
#include <functional>

struct Utils
{
	static void HashString(size_t& dataToFill, const char* stringToHash)
	{
		dataToFill = std::hash<std::string>{}(stringToHash);
	}
};