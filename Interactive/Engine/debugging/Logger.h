#pragma once
#include <cstdlib>
#include <iostream>
#include <sstream>

namespace TurtleEngine
{
	class Logger
	{
	public:
		static void LogError(std::string message)
		{
			time_t now = time(0);
			struct tm* tm_struct = new struct tm;
			localtime_s(tm_struct, &now);

			std::cout << "\033[31m";
			std::cout << "[" << tm_struct->tm_hour << ":" << tm_struct->tm_min << ":" << tm_struct->tm_sec << "] " << message << std::endl;
			delete tm_struct;

			std::cout << "\033[37m";
		}

		static void LogWarning(std::string message)
		{
			time_t now = time(0);
			struct tm* tm_struct = new struct tm;
			localtime_s(tm_struct, &now);

			std::cout << "\033[33m";
			std::cout << "[" << tm_struct->tm_hour << ":" << tm_struct->tm_min << ":" << tm_struct->tm_sec << "] " << message << "" << std::endl;
			delete tm_struct;

			std::cout << "\033[37m";
		}

		static void LogNormal(std::string message)
		{
			time_t now = time(0);
			struct tm* tm_struct = new struct tm;
			localtime_s(tm_struct, &now);

			std::cout << "\033[37m";
			std::cout << "[" << tm_struct->tm_hour << ":" << tm_struct->tm_min << ":" << tm_struct->tm_sec << "] " << message << "" << std::endl;
			delete tm_struct;
		}
	};
}
