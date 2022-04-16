#pragma once
#include "glm/vec2.hpp"

inline bool IsVec2EqualTo(glm::vec2 vecOne, glm::vec2 vecTwo, float errorMargin)
{
	if (fabs(vecOne.x - vecTwo.x) < errorMargin && fabs(vecOne.y - vecTwo.y) < errorMargin)
		return true;
	return false;
}
