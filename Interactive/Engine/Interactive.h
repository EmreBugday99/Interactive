#pragma once
#include <map>
#include <string>

class Entity;
class InteractiveObject;
class TextureManager;
class InputManager;
class Camera;
class EntityManager;
class Window;
class GarbageCollector;
class FactorySystem;
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
	FactorySystem* Factory;

	static std::map<std::string, InteractiveObject*> GlobalObjectPointers;

	Interactive(std::string gameName);
	~Interactive();

	void Start();
	void Update();

private:
	void Close();
};
