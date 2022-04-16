#include "ObstacleSystem.h"

#include "Engine.h"
#include "components/TransformComponent.hpp"
#include "../Components/ObstacleComponent.hpp"

void ObstacleSystem::MoveObstacles()
{
	const auto& obstacleView = TurtleCore::Engine::GetWorld().Registry
															.view<ObstacleComponent, TurtleCore::TransformComponent>();

	for (entt::entity obstacleEntity : obstacleView)
	{
		using namespace TurtleCore;

		ObstacleComponent& obstacleComponent = obstacleView.get<ObstacleComponent>(obstacleEntity);
		TransformComponent& transformComponent = obstacleView.get<TransformComponent>(obstacleEntity);

		if (obstacleComponent.swapDirection)
			transformComponent.Position -= 0.1f;
		else
			transformComponent.Position += 0.1f;

		obstacleComponent.swapDirection = !obstacleComponent.swapDirection;

	}
}
