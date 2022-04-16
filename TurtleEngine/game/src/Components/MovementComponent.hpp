#pragma once

struct MovementComponent
{
	bool CanMove;

	MovementComponent() : CanMove(false) {}

	MovementComponent(const MovementComponent& copied) = default;
};