#pragma once

namespace Interactive
{
	struct Entity
	{
		unsigned int EntityId;
		std::vector<unsigned int> ComponentTypes;
	};
}