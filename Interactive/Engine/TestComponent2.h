#pragma once
#include "components/Sprite2D.h"

class TestComponent2 : public Sprite2D
{
public:
	TestComponent2();
	
	void BeginPlay() override;

	void Update(float deltaTime) override;

	void Render() override;

	void KeyboardCallback() override;

	void SayHello();

protected:
	void OnMarkedForDestruction() override;
};
