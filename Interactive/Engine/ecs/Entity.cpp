#include "Entity.h"
#include "Component.h"

Entity::Entity(std::string entityName)
{
	EntityName = entityName;
}

Entity::~Entity() {}

void Entity::Update(float deltaTime)
{
	for (Component*& component : Components)
	{
		component->Update();
		component->Render();
	}
}

void Entity::Destroy() {}