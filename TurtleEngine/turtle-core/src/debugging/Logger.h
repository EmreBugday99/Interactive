#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "../TurtleCore.h"

namespace TurtleCore
{
	TURTLE_API class Logger
	{
	public:
		template<typename... TArgs>
		static void LogError(const TArgs&... args)
		{
			time_t now = time(0);
			struct tm* tm_struct = new struct tm;
			localtime_s(tm_struct, &now);

			std::cout << "\033[31m";
			std::cout << "[" << tm_struct->tm_hour << ":" << tm_struct->tm_min << ":" << tm_struct->tm_sec << "] ";

			const std::vector<std::string> unpackedStrings = { args... };
			for (auto string : unpackedStrings)
			{
				std::cout << string;
			}
			std::cout << std::endl;

			delete tm_struct;

			std::cout << "\033[37m";
		}

		template<typename... TArgs>
		static void LogWarning(const TArgs&... args)
		{
			time_t now = time(0);
			struct tm* tm_struct = new struct tm;
			localtime_s(tm_struct, &now);

			std::cout << "\033[33m";
			std::cout << "[" << tm_struct->tm_hour << ":" << tm_struct->tm_min << ":" << tm_struct->tm_sec << "] ";

			const std::vector<std::string> unpackedStrings = { args... };
			for (auto string : unpackedStrings)
			{
				std::cout << string;
			}
			std::cout << std::endl;

			delete tm_struct;

			std::cout << "\033[37m";
		}

		template<typename... TArgs>
		static void LogNormal(const TArgs&... args)
		{
			time_t now = time(0);
			struct tm* tm_struct = new struct tm;
			localtime_s(tm_struct, &now);

			std::cout << "\033[37m";
			std::cout << "[" << tm_struct->tm_hour << ":" << tm_struct->tm_min << ":" << tm_struct->tm_sec << "] ";

			const std::vector<std::string> unpackedStrings = {args...};
			for (auto string : unpackedStrings)
			{
				std::cout << string;
			}
			std::cout << std::endl;
			
			delete tm_struct;
		}
	};
}
