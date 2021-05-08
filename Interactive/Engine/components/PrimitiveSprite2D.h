#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "../ecs/Component.h"

class ShaderProgram;
class IndexBuffer;
class VertexBuffer;
class VertexArray;
class PrimitiveSprite2D : public Component
{
public:
	glm::vec3 Position;
	glm::vec2 Size;
	glm::vec4 Color;
	ShaderProgram* Shader;

	PrimitiveSprite2D(glm::vec3 position, glm::vec2 size, glm::vec4 color);
	virtual ~PrimitiveSprite2D() override;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	VertexArray* GetVAO() const { return VAO; }

protected:
	VertexArray* VAO;
};
