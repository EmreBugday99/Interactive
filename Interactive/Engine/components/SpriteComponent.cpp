#include "SpriteComponent.h"

#include <iostream>

#include "TransformComponent.hpp"
#include "../renderer/BufferManager.h"
#include "../renderer/ShaderManager.h"

namespace TurtleEngine
{
	SpriteComponent::SpriteComponent(const TransformComponent& transform)
		: Color(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)), TextureId(0), NeedsRecompiling(false)
	{
		const GLfloat vertices[] =
		{
			0,									0,									0,
			0,									transform.Size.y,					0,
			transform.Size.x,					transform.Size.y,					0,
			transform.Size.x,					0,									0
		};
		constexpr GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

		VAO = BufferManager::CreateVertexArray();
		VBO[0] = BufferManager::CreateVertexBuffer(VAO, 0, vertices, 3*4, 3);
		ElementCount = 6;
		IBO = BufferManager::CreateIndexBuffer(VAO, indices, ElementCount);

		bool successful = false;
		ProgramId = ShaderManager::CreateShader(successful, "default shader", "shaders/shader.vert", "shaders/basicShader.frag");

		if (successful == false)
			std::cerr << "Shader not created" << std::endl;
	}
}