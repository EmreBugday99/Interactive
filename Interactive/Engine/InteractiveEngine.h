#pragma once
#include <string>

class TextureManager;
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
	InputManager* InputSystem;
	TextureManager* TextureSystem;

	InteractiveEngine(std::string gameName);
	~InteractiveEngine();

	void Start();
	void Update();

private:
	void Close();
};
