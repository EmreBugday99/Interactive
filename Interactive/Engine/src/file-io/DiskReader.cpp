#include "DiskReader.h"
#include <fstream>
#include <sstream>

bool DiskReader::ReadString(std::string& stringToFill, std::string filePath)
{
	std::stringstream stringStream;
	std::ifstream file;

	try
	{
		file.open(filePath, std::ios::in);

		if (file.fail() == false)
			stringStream << file.rdbuf();
		file.close();

		stringToFill = stringStream.str();
		return true;
	}
	catch (std::exception& ex)
	{
		return false;
	}
}