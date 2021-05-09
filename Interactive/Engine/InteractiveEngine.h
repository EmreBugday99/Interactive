#pragma once
#include <string>

class InputManager;
class Camera;
class EntityManager;
class Window;
class InteractiveEngine
{
public:
	std::string GameName;
	Window* GameWindow;
	EntityManager* ECS;
	Camera* MainCamera;
	InputManager* InputController;

	InteractiveEngine(std::string gameName);
	~InteractiveEngine();

	void Start();
	void Update();

private:
	void Close();
};
