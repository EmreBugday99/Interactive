#pragma once
#include <iostream>

#include "../InteractiveObject.h"
#include "../includes/CoreIncludes.h"

class Entity : public InteractiveObject
{
private:
	friend class EntityManager;

	Entity(std::string entityName, Interactive* engine);

	/// <summary>
	/// Joins the components inside ComponentsWaitingToJoin vector into the ComponentsInGameLoop vector.
	/// </summary>
	void JoinComponentsIntoGameLoop();
	/// <summary>
	/// Removes components fro
	/// </summary>
	void RemoveComponentsFromGameLoop();

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

	/// <summary>
	/// Called every frame.
	/// </summary>
	/// <param name="deltaTime">Amount of time passed from the last frame to the current one.</param>
	void Update(float deltaTime);

	/// <summary>
	/// Creates a new component and attaches it to this entity.
	/// </summary>
	/// <typeparam name="T">Type of the component to add.</typeparam>
	/// <param name="...args">Arguments required for the component's construction.</param>
	/// <returns>Returns the created component pointer.</returns>
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

	/// <summary>
	/// Returns the first found component of that type.
	/// </summary>
	/// <typeparam name="T">Type of the component.</typeparam>
	/// <returns>Returns the component pointer if found one. Returns nullptr if not found.</returns>
	template <typename T>
	Component* GetComponentOfType() const
	{
		for (Component* component : ComponentsInGameLoop)
		{
			if (&typeid(*component) == &typeid(T))
				return component;
		}

		return nullptr;
	}

	/// <summary>
	/// Returns all the components of the specified type that this entity has.
	/// </summary>
	/// <typeparam name="T">Type of the component.</typeparam>
	/// <returns>Returns a vector of components. Returns an empty vector if not found any.</returns>
	template <typename T>
	std::vector<T*> GetComponentsOfType()
	{
		std::vector<T*> componentsToReturn;

		for (Component* component : ComponentsInGameLoop)
		{
			if (&typeid(*component) == &typeid(T))
				componentsToReturn.push_back(static_cast<T*>(component));
		}

		return componentsToReturn;
	}

	/// <summary>
	/// Only checks the components currently inside the game,
	/// excluding the ones that are waiting to enter.
	/// </summary>
	/// <typeparam name="T">Type of the component to check</typeparam>
	/// <returns>If the entity has such component</returns>
	template <typename T>
	bool HasComponentSimple()
	{
		for (Component* component : ComponentsInGameLoop)
		{
			if (&typeid(*component) == &typeid(T))
				return true;
		}

		return false;
	}

	/// <summary>
	/// Checks both the components currently in the game
	/// and the ones that are waiting to enter.
	/// </summary>
	/// <typeparam name="T">Type of the component to check</typeparam>
	/// <returns>If the entity has such component</returns>
	template <typename T>
	bool HasComponent()
	{
		for (Component* component : ComponentsWaitingToJoin)
		{
			if (&typeid(*component) == &typeid(T))
				return true;
		}

		for (Component* component : ComponentsInGameLoop)
		{
			if (&typeid(*component) == &typeid(T))
				return true;
		}

		return false;
	}

protected:
	void OnMarkedForDestruction() override;
};
