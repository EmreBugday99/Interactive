#include "SpriteComponent.h"
#include "TransformComponent.hpp"
#include "../graphics/opengl/BufferManager.h"
#include "../graphics/opengl/ShaderManager.h"
#include "../debugging/Logger.h"

namespace TurtleCore
{
	SpriteComponent::SpriteComponent(const TransformComponent& transform)
		: Color(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)), TextureId(0), NeedsRecompiling(false)
	{
		const GLfloat vertices[] =
		{
			0,					0,					0,
			0,					1,					0,
			1,					1,					0,
			1,					0,					0
		};
		constexpr GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

		VAO = BufferManager::CreateVertexArray();
		VBO[0] = BufferManager::CreateVertexBuffer(VAO, 0, vertices, 3 * 4, 3);
		ElementCount = 6;
		IBO = BufferManager::CreateIndexBuffer(VAO, indices, ElementCount);

		bool successful = false;
		ProgramId = ShaderManager::CreateShader(successful, "default shader", "assets/shaders/shader.vert", "assets/shaders/basicShader.frag");

		if (successful == false)
			Logger::LogError("Shader not created!");
	}
}