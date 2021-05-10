#include "Entity.h"

Entity::Entity(std::string entityName)
{
	EntityName = entityName;
}

Entity::~Entity() {}

void Entity::Update(float deltaTime)
{
	size_t componentCount = Components.size();
	while (componentCount)
	{
		componentCount--;

		if (Components[componentCount]->BeginPlayExecuted == false)
		{
			Components[componentCount]->BeginPlay();
		}

		Components[componentCount]->Update(deltaTime);
		Components[componentCount]->Render();
	}
}

void Entity::Destroy() {}

Component* Entity::GetComponent(Component* component)
{
	return nullptr;
}