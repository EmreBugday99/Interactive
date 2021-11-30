#pragma once
#include "world/World.h"

class TestWorld : public TurtleCore::World
{
public:
	void OnWorldLoad() override;
	void OnWorldUnloaded() override;
};
