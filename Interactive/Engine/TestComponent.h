#pragma once
#include <vector>
#include "components/Sprite2D.h"

class Camera;

class TestComponent : public Sprite2D
{
public:
	TestComponent();
	virtual ~TestComponent() override;

	void BeginPlay() override;
	void Update(float deltaTime) override;
	void Render() override;
	void KeyboardCallback() override;

protected:
	void OnMarkedForDestruction() override;
};
