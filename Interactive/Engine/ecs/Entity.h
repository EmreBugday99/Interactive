#pragma once
#include "../includes/CoreIncludes.h"

class Entity
{
public:
	InteractiveEngine* Engine;
	std::string EntityName;
	std::vector<Component*> Components;

	Entity(std::string entityName);
	~Entity();

	void Update(float deltaTime);
	void Destroy();
	Component* GetComponent(Component* component);

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
};
