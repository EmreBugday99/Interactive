#pragma once
#include <string>

class Entity;
class InteractiveObject;
class TextureManager;
class InputManager;
class Camera;
class EntityManager;
class Window;
class GarbageCollector;
class Interactive
{
public:
	std::string GameName;
	Window* GameWindow;
	EntityManager* ECManager;
	Camera* MainCamera;
	InputManager* InputSystem;
	TextureManager* TextureSystem;
	GarbageCollector* GC;

	Interactive(std::string gameName);
	~Interactive();

	void Start();
	void Update();

private:
	void Close();
};
