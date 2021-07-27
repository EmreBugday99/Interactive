#include "Component.h"
#include "../includes/CoreIncludes.h"

Component::Component()
	: AttachedTransform(nullptr), FirstUpdateExecuted(false), Owner(nullptr), InputController(nullptr),
	BeginPlayExecuted(false) {}

Component::~Component() {}

void Component::Initialize()
{
	BeginPlayExecuted = true;
}

void Component::BeginPlay() {}
void Component::Update(float deltaTime) {}
void Component::Render() {}
void Component::KeyboardCallback() {}

Transform* Component::GetTransform()
{
	if (AttachedTransform != nullptr)
		return AttachedTransform;

	AttachedTransform = Owner->GetComponentOfType<Transform>();
	return AttachedTransform;
}

void Component::OnMarkedForDestruction()
{
	InteractiveObject::OnMarkedForDestruction();

	Owner->ComponentsWaitingToLeave.push_back(this);
}