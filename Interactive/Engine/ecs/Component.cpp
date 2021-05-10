#include "Component.h"
#include "../input/Keys.h"
#include "../input/KeyActions.h"

Component::Component()
	: Owner(nullptr), Engine(nullptr),
	InputController(nullptr), BeginPlayExecuted(false)
{
}
Component::~Component()
{
}
void Component::BeginPlay()
{
	BeginPlayExecuted = true;
}
void Component::Update(float deltaTime)
{
}
void Component::Render()
{
}
void Component::KeyboardCallback(Keys key, KeyActions action)
{
}