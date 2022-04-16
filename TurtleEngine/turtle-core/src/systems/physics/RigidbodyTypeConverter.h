#pragma once
#include "RigidbodyType.hpp"
#include "include/box2d/b2_body.h"
#include "../../TurtleCore.h"

namespace TurtleCore
{
	class RigidbodyTypeConverter
	{
	public:
		TURTLE_API static b2BodyType ConvertToBox2D(RigidbodyType bodyType);
	};
}