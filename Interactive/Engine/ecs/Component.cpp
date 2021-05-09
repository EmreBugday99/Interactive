#include "Component.h"

Component::Component() : Owner(nullptr), Engine(nullptr), InputController(nullptr) {}
Component::~Component() {}

void Component::BeginPlay() {}
void Component::Update(float deltaTime) {}
void Component::Render() {}

void Component::KeyboardCallback(int key, int action) {}