#pragma once
#include "world/World.h"

class TutorialWorld : public TurtleCore::World
{
public:
	void OnWorldLoad() override;
	void OnWorldUnloaded() override;
};
