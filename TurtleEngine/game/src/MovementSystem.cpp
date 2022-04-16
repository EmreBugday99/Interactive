#include "MovementSystem.h"
#include "Engine.h"
#include "MovementComponent.hpp"
#include "components/TransformComponent.hpp"

void MovementSystem::MovementUpdate(float deltaTime)
{
	const auto view = TurtleCore::Engine::GetWorld().Registry.view<TurtleCore::TransformComponent, MovementComponent>();
	
	for (const entt::entity entity : view)
	{
		TurtleCore::TransformComponent& transform = view.get<TurtleCore::TransformComponent>(entity);

		if (TurtleCore::Engine::InputSystem->GetKeyState(TurtleCore::KeyCode::W).isDown)
			transform.Position.y += 0.01f;
		if (TurtleCore::Engine::InputSystem->GetKeyState(TurtleCore::KeyCode::S).isDown)
			transform.Position.y -= 0.01f;
		if (TurtleCore::Engine::InputSystem->GetKeyState(TurtleCore::KeyCode::A).isDown)
			transform.Position.x -= 0.01f;
		if (TurtleCore::Engine::InputSystem->GetKeyState(TurtleCore::KeyCode::D).isDown)
			transform.Position.x += 0.01f;

		if (TurtleCore::Engine::InputSystem->GetKeyState(TurtleCore::KeyCode::F).isDown)
		{
			transform.Size.x += 0.1f;
			transform.Size.t += 0.1f;
		}
		if (TurtleCore::Engine::InputSystem->GetKeyState(TurtleCore::KeyCode::G).isDown)
		{
			transform.Size.x -= 0.1f;
			transform.Size.y -= 0.1f;
		}
	}
}