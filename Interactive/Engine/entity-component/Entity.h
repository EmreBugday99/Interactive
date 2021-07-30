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

	bool HasComponent(const char* typeName)
	{
		for (Component* component : ComponentsInGameLoop)
		{
			if(*component->Reflection.GetTypeName() == *typeName)
			{
				return true;
			}
		}
		
		return false;
	}

	bool HasComponent(size_t typeHash)
	{
		for (Component* component : ComponentsInGameLoop)
		{
			if (component->Reflection.GetTypeHash() == typeHash)
			{
				return true;
			}
		}
		
		return false;
	}

	bool HasComponentComplex(const char* typeName)
	{
		for (Component* component : ComponentsInGameLoop)
		{
			if (*component->Reflection.GetTypeName() == *typeName)
			{
				return true;
			}
		}

		for (Component* component : ComponentsWaitingToJoin)
		{
			if (*component->Reflection.GetTypeName() == *typeName)
			{
				return true;
			}
		}

		return false;
	}

	bool HasComponentComplex(size_t typeHash)
	{
		for (Component* component : ComponentsInGameLoop)
		{
			if (component->Reflection.GetTypeHash() == typeHash)
			{
				return true;
			}
		}

		for (Component* component : ComponentsWaitingToJoin)
		{
			if (component->Reflection.GetTypeHash() == typeHash)
			{
				return true;
			}
		}

		return false;
	}

	Component* GetComponent(const char* typeName)
	{
		for (Component* component : ComponentsInGameLoop)
		{
			if (*component->Reflection.GetTypeName() == *typeName)
			{
				return component;
			}
		}

		return nullptr;
	}

	Component* GetComponent(size_t typeHash)
	{
		for (Component* component : ComponentsInGameLoop)
		{
			if (component->Reflection.GetTypeHash() == typeHash)
			{
				return component;
			}
		}

		return nullptr;
	}

	Component* GetComponentComplex(const char* typeName)
	{
		for (Component* component : ComponentsInGameLoop)
		{
			if (*component->Reflection.GetTypeName() == *typeName)
			{
				return component;
			}
		}

		for (Component* component : ComponentsWaitingToJoin)
		{
			if (*component->Reflection.GetTypeName() == *typeName)
			{
				return component;
			}
		}

		return nullptr;
	}

protected:
	void OnMarkedForDestruction() override;
};
