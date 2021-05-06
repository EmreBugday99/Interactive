#pragma once
#include <string>

class DiskReader
{
public:
	static bool ReadString(std::string& stringToFill, std::string filePath);
};
