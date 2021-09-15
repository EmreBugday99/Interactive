#pragma once
#include <map>

namespace Interactive
{
	struct Entity
	{
		unsigned int EntityId;
		std::map<unsigned int, void*> ComponentMap;

		Entity() : EntityId(0) {}
	};
}