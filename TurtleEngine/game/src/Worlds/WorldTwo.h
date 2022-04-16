#pragma once
#include "world/World.h"

class WorldTwo : public TurtleCore::World
{

public:
	void OnWorldLoad() override;


	void OnWorldUnloaded() override;

};