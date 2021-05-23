#pragma once
#include <vector>

#include "components/PrimitiveSprite2D.h"

class Camera;

class TestComponent : public PrimitiveSprite2D
{
public:
	PrimitiveSprite2D* OtherComponent;
	Camera* testCamera;
	std::vector<Entity*> testEntities;

	TestComponent();
	virtual ~TestComponent() override;

	void BeginPlay() override;
	void Update(float deltaTime) override;
	void Render() override;
	void KeyboardCallback() override;

protected:
	void OnMarkedForDestruction() override;
};
