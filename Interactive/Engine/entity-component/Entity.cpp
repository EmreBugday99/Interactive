#include "Entity.h"

Entity::Entity(std::string entityName, Interactive* engine)
	: EntityName(entityName)
{
	SetEnginePtr(engine);
	AddComponent<Transform>();
}

Entity::~Entity() {}

void Entity::Update(float deltaTime)
{
	if (ComponentsWaitingToJoin.empty() == false)
		JoinComponentsIntoGameLoop();

	size_t componentIndex = ComponentsInGameLoop.size();
	while (componentIndex)
	{
		componentIndex--;

		if(ComponentsInGameLoop[componentIndex]->FirstUpdateExecuted == false)
		{
			ComponentsInGameLoop[componentIndex]->FirstUpdateExecuted = true;
			ComponentsInGameLoop[componentIndex]->BeginPlay(deltaTime);
		}
		ComponentsInGameLoop[componentIndex]->Update(deltaTime);
		ComponentsInGameLoop[componentIndex]->Render();
	}

	if (ComponentsWaitingToLeave.empty() == false)
		RemoveComponentsFromGameLoop();
}

void Entity::JoinComponentsIntoGameLoop()
{
	size_t componentIndex = ComponentsWaitingToJoin.size();
	while (componentIndex)
	{
		componentIndex--;

		Component* componentToJoin = ComponentsWaitingToJoin[componentIndex];

		componentToJoin->Initialize();
		ComponentsInGameLoop.push_back(componentToJoin);

		ComponentsWaitingToJoin.erase(ComponentsWaitingToJoin.begin() + componentIndex);
	}

	// TODO: Do I really need to shrink at this point? This is an costly operation.
	// TODO: Need a smarter way to optimize memory usage.
	ComponentsWaitingToJoin.shrink_to_fit();
}

void Entity::RemoveComponentsFromGameLoop()
{
	// A graciously f*cked up O(n2) algorithm. Just... pretend it's not here.
	size_t componentIndex = ComponentsWaitingToLeave.size();
	while (componentIndex)
	{
		componentIndex--;

		Component* componentToLeave = ComponentsWaitingToLeave[componentIndex];

		size_t secondComponentIndex = ComponentsInGameLoop.size();
		while (secondComponentIndex)
		{
			secondComponentIndex--;

			Component* componentToCompareAgainst = ComponentsInGameLoop[secondComponentIndex];

			if (componentToLeave == componentToCompareAgainst)
			{
				ComponentsInGameLoop.erase(ComponentsInGameLoop.begin() + secondComponentIndex);
				ComponentsWaitingToLeave.erase(ComponentsWaitingToLeave.begin() + componentIndex);
			}
		}
	}

	// TODO: Do I really need to shrink at this point? This is an costly operation.
	// TODO: Need a smarter way to optimize memory usage.
	ComponentsInGameLoop.shrink_to_fit();
	ComponentsWaitingToLeave.shrink_to_fit();
}

void Entity::OnMarkedForDestruction()
{
	InteractiveObject::OnMarkedForDestruction();

	GetEnginePtr()->ECManager->EntitiesWaitingToLeave.push_back(this);

	// Since entity is responsible for managing all of it's components...
	// ... it's going to mark it's own components to get destroyed.
	for (Component* component : ComponentsInGameLoop)
	{
		component->MarkForDestruction();
	}
}