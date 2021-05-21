#include "includes/CoreIncludes.h"

Interactive::Interactive(std::string gameName)
	: GameName(gameName), MainCamera(nullptr)
{
	GameWindow = new Window(gameName, 800, 800, this);
	ECS = new EntityManager(this);
	InputSystem = new InputManager(this);
	TextureSystem = new TextureManager(this);
}

Interactive::~Interactive() {}

void Interactive::Start()
{
	Update();
}

void Interactive::Update()
{
	while (GameWindow->IsClosed() == false)
	{
		GameWindow->Clear();

		size_t entityIndex = ECS->Entities.size();
		while (entityIndex)
		{
			entityIndex--;
			Entity* currentEntity = ECS->Entities[entityIndex];

			if (currentEntity->IsMarkedForDestruction() == false)
				currentEntity->Update(0.1f);
		}

		GameWindow->Update();
	}

	Close();
}

void Interactive::Close()
{
	delete(GameWindow);
	GameWindow = nullptr;

	delete(ECS);
	ECS = nullptr;

	glfwTerminate();
}