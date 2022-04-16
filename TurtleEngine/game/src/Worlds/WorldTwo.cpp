#include "WorldTwo.h"
#include "components/TransformComponent.hpp"
#include "systems/render/Gl2DRendererSystem.h"
#include "../Systems/GoalSystem.h"
#include "../Systems/WinLoseSystem.h"
#include "components/SpriteComponent.h"
#include "../Components/MovementComponent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "../Components/GoalComponent.hpp"
#include "../Components/ObstacleComponent.hpp"
#include "../Systems/MovementSystem.h"

void WorldTwo::OnWorldLoad()
{
	SystemUpdateCallbacks.clear();

	SystemUpdateCallbacks.push_back(MovementSystem::MovementUpdate);
	SystemUpdateCallbacks.push_back(GoalSystem::Update);
	SystemUpdateCallbacks.push_back(WinLoseSystem::Update);
	SystemUpdateCallbacks.push_back(TurtleCore::Gl2DRendererSystem::Update);

	const auto playerEntity = CreateEntity();
	TurtleCore::TransformComponent& transform = Registry.emplace<TurtleCore::TransformComponent>(playerEntity);
	Registry.emplace<TurtleCore::SpriteComponent>(playerEntity, transform);
	Registry.emplace<MovementComponent>(playerEntity);
	Registry.emplace<PlayerComponent>(playerEntity);

	const auto goalEntity = CreateEntity();
	TurtleCore::TransformComponent& transform2 = Registry.emplace<TurtleCore::TransformComponent>(goalEntity);
	transform2.Position.y = 0.7f;
	transform2.Position.x = 0.5f;
	TurtleCore::SpriteComponent& goalSprite = Registry.emplace<TurtleCore::SpriteComponent>(goalEntity, transform2);
	Registry.emplace<GoalComponent>(goalEntity);
	goalSprite.Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	{
		const entt::entity obstacleEntity = CreateEntity();
		auto& obstacleTransform = Registry.emplace<TurtleCore::TransformComponent>(obstacleEntity);
		obstacleTransform.Position = glm::vec2(0.0f, 0.5f);
		auto& obstacleSprite = Registry.emplace<TurtleCore::SpriteComponent>(obstacleEntity, obstacleTransform);
		obstacleSprite.Color = glm::vec4(0.6, 0.1, 0.2, 1.0f);
		Registry.emplace<ObstacleComponent>(obstacleEntity);
	}

	{
		const entt::entity obstacleEntity = CreateEntity();
		auto& obstacleTransform = Registry.emplace<TurtleCore::TransformComponent>(obstacleEntity);
		obstacleTransform.Position = glm::vec2(0.0f, 0.2f);
		auto& obstacleSprite = Registry.emplace<TurtleCore::SpriteComponent>(obstacleEntity, obstacleTransform);
		obstacleSprite.Color = glm::vec4(0.6, 0.1, 0.2, 1.0f);
		Registry.emplace<ObstacleComponent>(obstacleEntity);
	}

	for (int i = 1; i < 4; ++i)
	{
		const entt::entity obstacleEntity = CreateEntity();
		auto& obstacleTransform = Registry.emplace<TurtleCore::TransformComponent>(obstacleEntity);
		obstacleTransform.Position = glm::vec2(0.1f * static_cast<float>(i), 0.1f);
		auto& obstacleSprite = Registry.emplace<TurtleCore::SpriteComponent>(obstacleEntity, obstacleTransform);
		obstacleSprite.Color = glm::vec4(0.6, 0.1, 0.2, 1.0f);
		Registry.emplace<ObstacleComponent>(obstacleEntity);
	}

	for (int i = 2; i < 4; ++i)
	{
		const entt::entity obstacleEntity = CreateEntity();
		auto& obstacleTransform = Registry.emplace<TurtleCore::TransformComponent>(obstacleEntity);
		obstacleTransform.Position = glm::vec2(0.1f, 0.1f * static_cast<float>(i));
		auto& obstacleSprite = Registry.emplace<TurtleCore::SpriteComponent>(obstacleEntity, obstacleTransform);
		obstacleSprite.Color = glm::vec4(0.6, 0.1, 0.2, 1.0f);
		Registry.emplace<ObstacleComponent>(obstacleEntity);
	}

	for (int i = 1; i < 6; ++i)
	{
		const entt::entity obstacleEntity = CreateEntity();
		auto& obstacleTransform = Registry.emplace<TurtleCore::TransformComponent>(obstacleEntity);
		obstacleTransform.Position = glm::vec2(0.1f * static_cast<float>(i), 0.5f);
		auto& obstacleSprite = Registry.emplace<TurtleCore::SpriteComponent>(obstacleEntity, obstacleTransform);
		obstacleSprite.Color = glm::vec4(0.6, 0.1, 0.2, 1.0f);
		Registry.emplace<ObstacleComponent>(obstacleEntity);
	}

	for (int i = 1; i < 6; ++i)
	{
		const entt::entity obstacleEntity = CreateEntity();
		auto& obstacleTransform = Registry.emplace<TurtleCore::TransformComponent>(obstacleEntity);
		obstacleTransform.Position = glm::vec2(0.7f, 0.1f * static_cast<float>(i));
		auto& obstacleSprite = Registry.emplace<TurtleCore::SpriteComponent>(obstacleEntity, obstacleTransform);
		obstacleSprite.Color = glm::vec4(0.6, 0.1, 0.2, 1.0f);
		Registry.emplace<ObstacleComponent>(obstacleEntity);
	}
}

void WorldTwo::OnWorldUnloaded()
{
}
