#include "Entity.h"

#include <iostream>

Entity::Entity(std::string entityName, Interactive* engine)
	: EntityName(entityName)
{
	SetEnginePtr(engine);
}

Entity::~Entity() {}

void Entity::Update(float deltaTime)
{
	JoinComponentsIntoGameLoop();

	size_t componentIndex = ComponentsInGameLoop.size();
	while (componentIndex)
	{
		componentIndex--;

		if (ComponentsInGameLoop[componentIndex]->BeginPlayExecuted == false)
			ComponentsInGameLoop[componentIndex]->BeginPlay();

		ComponentsInGameLoop[componentIndex]->Update(deltaTime);
		ComponentsInGameLoop[componentIndex]->Render();
	}

	RemoveComponentsFromGameLoop();
}

void Entity::JoinComponentsIntoGameLoop()
{
	size_t componentIndex = ComponentsWaitingToJoin.size();
	while (componentIndex)
	{
		componentIndex--;

		Component* componentToJoin = ComponentsWaitingToJoin[componentIndex];
		ComponentsInGameLoop.push_back(componentToJoin);
	}

	ComponentsWaitingToJoin.clear();
}

void Entity::RemoveComponentsFromGameLoop()
{
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
				ComponentsInGameLoop.erase(ComponentsInGameLoop.begin() + secondComponentIndex);
		}
	}

	ComponentsWaitingToLeave.clear();
}

void Entity::OnMarkedForDestruction()
{
	InteractiveObject::OnMarkedForDestruction();

	std::cout << "I have been violently murdered! Please call 911! \n";
	
	GetEnginePtr()->ECS->EntitiesWaitingToLeave.push_back(this);

	for (Component* component : ComponentsInGameLoop)
	{
		component->MarkForDestruction();
		ComponentsWaitingToLeave.push_back(component);
	}
}