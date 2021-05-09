#pragma once

class InputManager;
class InteractiveEngine;
class Entity;
class Component
{
public:
	Entity* Owner;
	InteractiveEngine* Engine;
	InputManager* InputController;

	Component();
	virtual ~Component();

	virtual void BeginPlay();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void KeyboardCallback(int key, int action);
};
