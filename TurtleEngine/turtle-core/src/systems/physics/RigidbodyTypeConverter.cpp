#include "RigidbodyTypeConverter.h"
#include "../../components/Rigidbody2DComponent.h"
#include "include/box2d/b2_body.h"
#include "../../debugging/Logger.h"

b2BodyType TurtleCore::RigidbodyTypeConverter::ConvertToBox2D(RigidbodyType bodyType)
{
	switch (bodyType)
	{
	case RigidbodyType::Static:
		return b2_staticBody;
	case RigidbodyType::Dynamic:
		return b2_dynamicBody;
	case RigidbodyType::Kinematic:
		return b2_kinematicBody;
	}

	Logger::LogError("Invalid Body Type Provided! [", std::to_string(static_cast<int>(bodyType)), "]");
	return b2_staticBody;
}
