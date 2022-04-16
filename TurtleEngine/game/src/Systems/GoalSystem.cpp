#include "GoalSystem.h"

#include "Engine.h"
#include "components/TransformComponent.hpp"
#include "external/entt/entt.hpp"
#include "../Components/GoalComponent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "../VectorEqualChecker.h"
#include "../Worlds/WorldTwo.h"

void GoalSystem::Update(float deltaTime)
{
	const auto goalView = TurtleCore::Engine::GetWorld().Registry.view<TurtleCore::TransformComponent, GoalComponent>();
	const auto playerView = TurtleCore::Engine::GetWorld().Registry.view<TurtleCore::TransformComponent, PlayerComponent>();

	for (const entt::entity goalEntity : goalView)
	{
		TurtleCore::TransformComponent& goalTransform = goalView.get<TurtleCore::TransformComponent>(goalEntity);

		for (const entt::entity playerEntity : playerView)
		{
			if (goalEntity == playerEntity)
				continue;

			TurtleCore::TransformComponent& playerTransform = playerView.get<TurtleCore::TransformComponent>(playerEntity);

			if (IsVec2EqualTo(goalTransform.Position, playerTransform.Position, 0.05f))
			{
				TurtleCore::Engine::LoadWorld<WorldTwo>();
			}
		}
	}
}