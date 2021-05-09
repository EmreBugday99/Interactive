#include "InteractiveEngine.h"
#include "ecs/Entity.h"
#include "ecs/EntityManager.h"
#include "input/InputManager.h"
#include "renderer/Window.h"

InteractiveEngine::InteractiveEngine(std::string gameName)
	: GameName(gameName), MainCamera(nullptr)
{
	GameWindow = new Window(gameName, 800, 800, this);
	ECS = new EntityManager(this);
	InputController = new InputManager(this);
}

InteractiveEngine::~InteractiveEngine() {}

void InteractiveEngine::Start()
{
	Update();
}

void InteractiveEngine::Update()
{
	while (GameWindow->IsClosed() == false)
	{
		GameWindow->Clear();

		size_t entityCount = ECS->Entities.size();
		while (entityCount)
		{
			entityCount--;

			ECS->Entities[entityCount]->Update(0.1f);
		}

		GameWindow->Update();
	}

	Close();
}

void InteractiveEngine::Close()
{
	delete(GameWindow);
	GameWindow = nullptr;

	delete(ECS);
	ECS = nullptr;

	glfwTerminate();
}