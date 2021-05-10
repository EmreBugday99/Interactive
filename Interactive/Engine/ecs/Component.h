#pragma once

enum class Keys;
enum class KeyActions;
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
	virtual void KeyboardCallback(Keys key, KeyActions actions);

private:
	friend class Entity;
	bool BeginPlayExecuted;
};
