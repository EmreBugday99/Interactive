#pragma once
#include "../InteractiveObject.h"

class Entity;
enum class Keys;
enum class KeyActions;
class InputManager;
class Interactive;
class Component : public InteractiveObject
{
public:
	Entity* Owner;
	InputManager* InputController;

	Component();
	~Component() override;

	virtual void BeginPlay();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void KeyboardCallback();

protected:
	void OnMarkedForDestruction() override;

private:
	friend class Entity;

	bool BeginPlayExecuted;
};