#pragma once
#include "Entity.hpp"
namespace Interactive
{
	struct Component
	{
		unsigned int TypeId;
		Interactive::Entity* Entity;
		unsigned int ComponentId;
	};
}