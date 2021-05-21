#pragma once
#include "../includes/CoreIncludes.h"

class Entity
{
private:
	friend class EntityManager;
	Entity(std::string entityName);

	bool MarkedForDestruction;

public:
	Interactive* Engine;
	std::string EntityName;
	std::vector<Component*> Components;

	~Entity();

	void Update(float deltaTime);
	void DestroyEntity();

	template <typename T, typename... TArgs>
	T* AddComponent(TArgs... args)
	{
		T* newComponent = new T(std::forward<TArgs>(args)...);

		newComponent->Owner = this;
		newComponent->Engine = Engine;
		newComponent->InputController = Engine->InputSystem;
		Components.push_back(newComponent);

		return newComponent;
	}

	bool IsMarkedForDestruction() const { return MarkedForDestruction; }
};
