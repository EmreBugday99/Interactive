#pragma once

class Camera;
class EntityManager;
class BaseRenderer;
class Window;
class InteractiveEngine
{
public:
	Window* GameWindow;
	BaseRenderer* Renderer;
	EntityManager* ECS;
	Camera* MainCamera;

	InteractiveEngine();
	~InteractiveEngine();

	void Initialize();
	void Start();
	void Update();

private:
	void Close();
};

