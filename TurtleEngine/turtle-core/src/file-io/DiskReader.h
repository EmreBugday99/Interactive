#pragma once
#include <string>

namespace TurtleCore
{
	class DiskReader
	{
	public:
		static bool ReadString(std::string& stringToFill, std::string filePath);
	};
}
