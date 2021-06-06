#pragma once
#include "entity-component/Component.h"

class TestComponent2 : public Component
{
public:
	void BeginPlay() override;

	void Update(float deltaTime) override;

	void Render() override;

	void KeyboardCallback() override;

	void SayHello();

protected:
	void OnMarkedForDestruction() override;
};
