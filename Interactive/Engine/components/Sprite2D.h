#pragma once

#include "../includes/CoreIncludes.h"

class Transform;
class Texture;
class ShaderProgram;
class IndexBuffer;
class VertexBuffer;
class VertexArray;
class Sprite2D : public Component
{
public:
	glm::vec4 Color{};
	ShaderProgram* Shader;

	Sprite2D(glm::vec3 position, glm::vec2 size, glm::vec4 color);
	Sprite2D();
	~Sprite2D() override;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
	void AttachTexture(Texture* textureToAttach);

	VertexArray* GetVAO() const { return VAO; }


	void BeginPlay() override;

protected:
	VertexArray* VAO;

	void OnMarkedForDestruction() override;

private:
	friend class Transform;

	Texture* AttachedTexture;

	void CreateSprite2D();
	/// <summary>
	/// Resets the VBO layout according to the component's size.
	/// </summary>
	void UpdateSprite();
};
