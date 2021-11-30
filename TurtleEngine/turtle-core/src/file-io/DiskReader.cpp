#include "DiskReader.h"
#include <fstream>
#include <sstream>
#include "../debugging/Logger.h"

namespace TurtleCore
{
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
			Logger::LogError("Failed to read file from disk at path: ", filePath);
			return false;
		}
	}
}