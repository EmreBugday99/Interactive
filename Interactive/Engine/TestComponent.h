#pragma once
#include "entity-component/Component.h"

class TestComponent : public Component
{
public:
	TestComponent();
	~TestComponent() override;

	void Initialize() override;
	void BeginPlay() override;
	void Update(float deltaTime) override;
	void Render() override;
	void KeyboardCallback() override;

protected:
	void OnMarkedForDestruction() override;
};
