#include "includes/CoreIncludes.h"

std::map<std::string, InteractiveObject*> Interactive::GlobalObjectPointers;

Interactive::Interactive(std::string gameName)
	: GameName(gameName), MainCamera(nullptr)
{
	GameWindow = new Window(gameName, 800, 800, this);
	ECManager = new EntityManager(this);
	InputSystem = new InputManager(this);
	TextureSystem = new TextureManager(this);
	GC = new GarbageCollector(this);
	Factory = new ComponentFactory(this);
	AssetSystem = new AssetManager(this);
	AssetSystem->InitializeDatabase();

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(GameWindow->GlWindow, true);
	ImGui_ImplOpenGL3_Init("#version 150");
	ImGui::StyleColorsDark();

	GlobalObjectPointers.emplace("null", nullptr);
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
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

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

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		GameWindow->Update();

		ECManager->RemoveEntitiesFromGameLoop();
	}

	Close();
}

void Interactive::Close()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete(GameWindow);
	GameWindow = nullptr;

	delete(ECManager);
	ECManager = nullptr;

	delete(InputSystem);
	InputSystem = nullptr;

	delete(TextureSystem);
	TextureSystem = nullptr;

	delete(GC);
	GC = nullptr;

	delete(Factory);
	Factory = nullptr;

	glfwTerminate();
}