#pragma once
#include "../InteractiveObject.h"

class ReflectionSystem;
class Transform;
class Entity;
enum class Keys;
enum class KeyActions;
class InputManager;
class Interactive;
class Component : public InteractiveObject
{
private:
	Transform* AttachedTransform;
	bool FirstUpdateExecuted;
	
public:
	Entity* Owner;
	InputManager* InputController;
	std::vector<ClassReflection> Dependencies;

	Component();
	~Component() override;

	/// <summary>
	/// Called when this component joins the game loop
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// Called when this component enters it's first update loop
	/// </summary>
	virtual void BeginPlay();
	/// <summary>
	/// Called each frame
	/// </summary>
	virtual void Update(float deltaTime);
	/// <summary>
	/// Called each frame, for rendering
	/// </summary>
	virtual void Render();

	Transform* GetTransform();

protected:
	void OnMarkedForDestruction() override;

private:
	friend class Entity;

	bool BeginPlayExecuted;
};
