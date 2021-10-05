#pragma once

#include <glm/vec4.hpp>
#include "../renderer/buffers/VertexArray.h"
#include "../renderer/shader/ShaderProgram.h"

namespace IE
{
	struct SpriteComponent
	{
		glm::vec4 Color;
		ShaderProgram Shader;
		VertexArray VAO;
	};
}