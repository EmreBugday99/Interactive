#pragma once
#include "../InteractiveObject.h"
#include "../includes/CoreIncludes.h"

class Entity : public InteractiveObject
{
private:
	friend class EntityManager;

	Entity(std::string entityName, Interactive* engine);

public:
	std::string EntityName;
	/// <summary>
	/// Components that are waiting to be initialized and enter the game loop.
	/// </summary>
	std::vector<Component*> ComponentsWaitingToJoin;
	/// <summary>
	/// Components that are currently in the game loop.
	/// </summary>
	std::vector<Component*> ComponentsInGameLoop;
	/// <summary>
	/// Components that are waiting to leave the game loop and get destroyed/garbage collected.
	/// </summary>
	std::vector<Component*> ComponentsWaitingToLeave;

	~Entity() override;

	void Update(float deltaTime);

	template <typename T, typename... TArgs>
	T* AddComponent(TArgs... args)
	{
		T* newComponent = new T(std::forward<TArgs>(args)...);
		newComponent->SetEnginePtr(GetEnginePtr());

		newComponent->Owner = this;
		newComponent->InputController = GetEnginePtr()->InputSystem;
		ComponentsWaitingToJoin.push_back(newComponent);

		return newComponent;
	}

protected:
	void JoinComponentsIntoGameLoop();
	void RemoveComponentsFromGameLoop();

	void OnMarkedForDestruction() override;
};
