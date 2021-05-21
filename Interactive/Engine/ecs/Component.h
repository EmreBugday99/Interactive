#pragma once

enum class Keys;
enum class KeyActions;
class InputManager;
class Interactive;
class Entity;
class Component
{
public:
	Entity* Owner;
	Interactive* Engine;
	InputManager* InputController;

	Component();
	virtual ~Component();

	virtual void BeginPlay();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void KeyboardCallback();
	void DestroyComponent();

	bool IsMarkedForDestruction() const { return MarkedForDestruction; }

private:
	friend class Entity;
	bool BeginPlayExecuted;
	bool MarkedForDestruction;
};
