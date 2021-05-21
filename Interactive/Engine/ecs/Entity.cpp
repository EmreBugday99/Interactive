#include "Entity.h"

Entity::Entity(std::string entityName)
{
	EntityName = entityName;
}

Entity::~Entity() {}

void Entity::Update(float deltaTime)
{
	size_t componentIndex = Components.size();
	while (componentIndex)
	{
		componentIndex--;

		if (Components[componentIndex]->BeginPlayExecuted == false)
			Components[componentIndex]->BeginPlay();

		Components[componentIndex]->Update(deltaTime);
		Components[componentIndex]->Render();
	}
}

void Entity::DestroyEntity()
{
	MarkedForDestruction = true;

	//size_t entityIndex = Engine->ECS->Entities.size();
	//while (entityIndex)
	//{
	//	entityIndex--;

	//	if (this == Engine->ECS->Entities[entityIndex])
	//	{
	//		Engine->ECS->Entities.erase(Engine->ECS->Entities.begin() - entityIndex);
	//		break;
	//	}
	//}
}