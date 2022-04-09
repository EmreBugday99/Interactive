#pragma once
#include <functional>
#include "../components/TransformComponent.hpp"
#include <iosfwd>
#include <sstream>

namespace TurtleCore
{
	struct Utils
	{
		static void HashString(size_t& dataToFill, const char* stringToHash)
		{
			dataToFill = std::hash<std::string>{}(stringToHash);
		}

		static std::string Vec2ToString(glm::vec2 pos)
		{
			std::stringstream ss = std::stringstream();
			ss << "X: " << pos.x << " Y: " << pos.y;

			return ss.str();
		}
	};
}
