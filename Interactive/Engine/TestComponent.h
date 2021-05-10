#pragma once
#include "components/PrimitiveSprite2D.h"

class TestComponent : public PrimitiveSprite2D
{
public:
	PrimitiveSprite2D* OtherComponent;

	TestComponent();
	virtual ~TestComponent() override;

	void BeginPlay() override;
	void Update(float deltaTime) override;
	void Render() override;
	void KeyboardCallback(Keys key, KeyActions actions) override;

	bool IsColliding();
};
