#pragma once
#include "entity-component/Component.h"

class TestComponent2 : public Component
{
public:
	~TestComponent2() override;
	void Initialize() override;
	void BeginPlay() override;
	void Update(float deltaTime) override;
	void Render() override;
	void KeyboardCallback() override;
protected:
	void OnMarkedForDestruction() override;
};
