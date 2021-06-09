#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "../entity-component/Component.h"

class Transform : public Component
{
private:
	glm::vec2 Size;

public:
	glm::vec3 Position;

	Transform();

	void BeginPlay() override;
	void Update(float deltaTime) override;

	glm::vec2 GetSize() const { return Size; }

	void SetPosition(glm::vec3 newPosition);
	void SetSize(glm::vec2 newSize);
};
