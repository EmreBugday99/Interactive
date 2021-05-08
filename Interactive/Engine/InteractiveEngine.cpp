#include "InteractiveEngine.h"
#include "ecs/Entity.h"
#include "ecs/EntityManager.h"
#include "renderer/Window.h"
#include "renderer/renderers/BaseRenderer.h"

InteractiveEngine::InteractiveEngine()
{
	GameWindow = nullptr;
	Renderer = nullptr;
	ECS = nullptr;
	MainCamera = nullptr;
}

InteractiveEngine::~InteractiveEngine() {}

void InteractiveEngine::Initialize()
{
	GameWindow = new Window("Test Engine", 800, 800);
	GameWindow->Engine = this;

	ECS = new EntityManager();
	ECS->Engine = this;

	Renderer = new BaseRenderer();
	Renderer->Engine = this;
}

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
		Renderer->Render();

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

	delete(Renderer);
	Renderer = nullptr;

	glfwTerminate();
}