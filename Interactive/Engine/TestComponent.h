#pragma once
#include <vector>
#include "components/PrimitiveSprite2D.h"

class Camera;

class TestComponent : public PrimitiveSprite2D
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
