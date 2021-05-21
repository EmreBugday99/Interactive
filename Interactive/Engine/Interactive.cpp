#include "includes/CoreIncludes.h"

Interactive* Interactive::EngineInstance(nullptr);

Interactive::Interactive(std::string gameName)
	: GameName(gameName), MainCamera(nullptr)
{
	if (EngineInstance != nullptr)
	{
		delete(this);
		return;
	}

	EngineInstance = this;
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

		ECS->JoinEntitiesIntoGameLoop();

		size_t entityIndex = ECS->EntitiesInGameLoop.size();
		while (entityIndex)
		{
			entityIndex--;
			Entity* currentEntity = ECS->EntitiesInGameLoop[entityIndex];

			currentEntity->Update(0.1f);
		}

		GameWindow->Update();

		ECS->RemoveEntitiesFromGameLoop();
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