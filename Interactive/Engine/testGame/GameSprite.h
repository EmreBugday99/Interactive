#pragma once
#include "../components/Sprite2D.h"

class GameSprite : public Sprite2D
{
public:
	void Initialize() override;
	void BeginPlay() override;
};

