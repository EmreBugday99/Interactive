#pragma once

struct PlayerComponent
{
	int Health = 100;

	PlayerComponent() = default;
	PlayerComponent(const PlayerComponent& other) = default;
};