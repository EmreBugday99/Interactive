#include "includes/CoreIncludes.h"

Interactive::Interactive(std::string gameName)
	: GameName(gameName), MainCamera(nullptr)
{
	GameWindow = new Window(gameName, 800, 800, this);
	ECManager = new EntityManager(this);
	InputSystem = new InputManager(this);
	TextureSystem = new TextureManager(this);
	GC = new GarbageCollector(this);
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

		if (GC->GetGCQueueSize() >= GC->ForceEnterThreshold)
			GC->CollectGarbage();

		ECManager->JoinEntitiesIntoGameLoop();

		size_t entityIndex = ECManager->EntitiesInGameLoop.size();
		while (entityIndex)
		{
			entityIndex--;
			Entity* currentEntity = ECManager->EntitiesInGameLoop[entityIndex];

			// TODO: Put real delta time here instead of 0.1f
			currentEntity->Update(0.1f);
		}

		GameWindow->Update();

		ECManager->RemoveEntitiesFromGameLoop();
	}

	Close();
}

void Interactive::Close()
{
	delete(GameWindow);
	GameWindow = nullptr;

	delete(ECManager);
	ECManager = nullptr;

	glfwTerminate();
}