#include "includes/CoreIncludes.h"

InteractiveEngine::InteractiveEngine(std::string gameName)
	: GameName(gameName), MainCamera(nullptr)
{
	GameWindow = new Window(gameName, 800, 800, this);
	ECS = new EntityManager(this);
	InputSystem = new InputManager(this);
	TextureSystem = new TextureManager(this);
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