#include "Component.h"
#include "../includes/CoreIncludes.h"
#include "../reflection-system/ReflectionSystem.hpp"

Component::Component()
	: AttachedTransform(nullptr), FirstUpdateExecuted(false), Owner(nullptr), InputController(nullptr),
	BeginPlayExecuted(false)
{
	ReflectionSystem::UpdateClassReflection<Component>(Reflection, "Component");
}

Component::~Component() {}

void Component::Initialize()
{
	BeginPlayExecuted = true;
}

void Component::BeginPlay() {}
void Component::Update(float deltaTime) {}
void Component::Render() {}

Transform* Component::GetTransform()
{
	if (AttachedTransform != nullptr)
		return AttachedTransform;

	AttachedTransform = static_cast<Transform*>(Owner->GetComponent("Transform"));
	return AttachedTransform;
}

void Component::OnMarkedForDestruction()
{
	InteractiveObject::OnMarkedForDestruction();

	Owner->ComponentsWaitingToLeave.push_back(this);
}