#include "WinLoseSystem.h"
#include "Engine.h"
#include "../Components/ObstacleComponent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "debugging/Logger.h"
#include "components/TransformComponent.hpp"
#include "../VectorEqualChecker.h"

void WinLoseSystem::Update(float deltaTime)
{
	const auto& obstacleView = TurtleCore::Engine::GetWorld().Registry.view<ObstacleComponent, TurtleCore::TransformComponent>();
	const auto& playerView = TurtleCore::Engine::GetWorld().Registry.view<PlayerComponent, TurtleCore::TransformComponent>();

	for (entt::entity playerEntity : playerView)
	{
		using namespace TurtleCore;

		PlayerComponent& playerComponent = playerView.get<PlayerComponent>(playerEntity);
		TransformComponent& playerTransform = playerView.get<TransformComponent>(playerEntity);


		if (playerComponent.Health <= 0)
		{
			Logger::LogWarning("Your dead dude");
			Engine::GetWorld().Registry.destroy(playerEntity);
			return;
		}

		for (entt::entity obstacleEntity : obstacleView)
		{
			TransformComponent& obstacleTransform = obstacleView.get<TransformComponent>(obstacleEntity);

			if (playerEntity == obstacleEntity)
			{
				Logger::LogError("Skipping due to identical entities!");
				continue;
			}

			if (Engine::GetWorld().IsLoaded == false)
				return;

			if (IsVec2EqualTo(obstacleTransform.Position, playerTransform.Position, 0.05f))
			{
				playerComponent.Health -= 25;
				playerTransform.Position = glm::vec2(0.0f, 0.0f);
				TurtleCore::Logger::LogError("Hit obstacle! Remaining health: ", std::to_string(playerComponent.Health));
			}
		}
	}
}