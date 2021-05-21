#pragma once
#include <string>

class TextureManager;
class InputManager;
class Camera;
class EntityManager;
class Window;
class Interactive
{
public:
	std::string GameName;
	Window* GameWindow;
	EntityManager* ECS;
	Camera* MainCamera;
	InputManager* InputSystem;
	TextureManager* TextureSystem;

	Interactive(std::string gameName);
	~Interactive();

	void Start();
	void Update();

private:
	void Close();
};