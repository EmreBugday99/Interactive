#pragma once
class Entity;

namespace Interactive
{
	struct Component
	{
		unsigned int TypeId;
		Entity* EntityId;
		unsigned int ComponentId;
	};
}