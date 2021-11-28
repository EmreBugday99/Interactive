#pragma once
#include "World/World.h"

class TestWorld : public TurtleEngine::World
{
public:
	void OnWorldLoad() override;
};

