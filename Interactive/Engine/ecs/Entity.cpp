#include "Entity.h"
#include "Component.h"

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

		Components[componentCount]->Update(deltaTime);
		Components[componentCount]->Render();
	}
}

void Entity::Render()
{
}

void Entity::Destroy() {}