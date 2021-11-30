#pragma once

#include <vec4.hpp>
#include <glad/glad.h>

namespace TurtleCore
{
	struct TransformComponent;
	struct SpriteComponent
	{
		glm::vec4 Color;
		GLuint VAO;
		/*
		 * Layout Structure:
		 * 1st Layout -> Coordinate Layout
		 * 2nd Layout -> Texture Layout
		 */
		GLuint VBO[2]{};
		GLuint IBO;
		GLsizei ElementCount;
		GLuint ProgramId;
		GLuint TextureId;
		bool NeedsRecompiling;

		SpriteComponent(const TransformComponent& transform);

		SpriteComponent(const SpriteComponent& copied) :
			Color(glm::vec4(copied.Color.x, copied.Color.y, copied.Color.z, copied.Color.w)), VAO(copied.VAO),
			IBO(copied.IBO), ElementCount(copied.ElementCount), ProgramId(copied.ProgramId),
			TextureId(copied.TextureId), NeedsRecompiling(copied.NeedsRecompiling) {}
	};
}