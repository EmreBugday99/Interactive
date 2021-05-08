#pragma once
#include <string>
#include <vector>

class Component;
class Entity
{
public:
	std::string EntityName;
	std::vector<Component*> Components;
	
	Entity(std::string entityName);
	~Entity();

	void Update(float deltaTime);
	void Destroy();

	template <typename T, typename... TArgs>
	T* AddComponent(TArgs... args)
	{
		T* newComponent = new T(std::forward<TArgs>(args)...);

		newComponent->Owner = this;
		Components.push_back(newComponent);

		return newComponent;
	}
};
