#include "TutorialWorld.h"

#include <thread>

#include "Engine.h"
#include "components/SpriteComponent.h"
#include "components/TransformComponent.hpp"
#include "external/entt/entt.hpp"
#include "systems/render/Gl2DRendererSystem.h"
#include "debugging/Logger.h"
#include "../Systems/GoalSystem.h"
#include "../Components/MovementComponent.hpp"
#include "../Components/GoalComponent.hpp"
#include "../Systems/MovementSystem.h"
#include "../Components/PlayerComponent.hpp"
#include "../Systems/WinLoseSystem.h"

void TutorialWorld::OnWorldLoad()
{
	SystemUpdateCallbacks.push_back(MovementSystem::MovementUpdate);
	SystemUpdateCallbacks.push_back(GoalSystem::Update);
	SystemUpdateCallbacks.push_back(WinLoseSystem::Update);
	SystemUpdateCallbacks.push_back(TurtleCore::Gl2DRendererSystem::Update);

	const auto playerEntity = CreateEntity();
	TurtleCore::TransformComponent& transform = Registry.emplace<TurtleCore::TransformComponent>(playerEntity);
	transform.Position.x = 0.4f;
	transform.Position.y = 0.1f;
	Registry.emplace<TurtleCore::SpriteComponent>(playerEntity, transform);
	Registry.emplace<MovementComponent>(playerEntity);
	Registry.emplace<PlayerComponent>(playerEntity);

	const auto goalEntity = CreateEntity();
	TurtleCore::TransformComponent& transform2 = Registry.emplace<TurtleCore::TransformComponent>(goalEntity);
	transform2.Position.y = 0.3f;
	transform2.Position.x = 0.5f;
	TurtleCore::SpriteComponent& goalSprite = Registry.emplace<TurtleCore::SpriteComponent>(goalEntity, transform2);
	Registry.emplace<GoalComponent>(goalEntity);
	goalSprite.Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	MovementSystem::Initialize();
	//std::thread voiceMovementThread(MovementSystem::MovementUpdate);
	//voiceMovementThread.detach();
}

void TutorialWorld::OnWorldUnloaded()
{
	Registry.each([this](entt::entity entity)
		{
			Registry.destroy(entity);
		});
}