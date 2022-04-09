#pragma once
#include "glad/glad.h"

namespace TurtleCore
{
	class BufferManager
	{
	public:
		static GLuint CreateVertexArray();
		static GLuint CreateVertexBuffer(const GLuint& vao, GLuint layoutIndex, const GLfloat* vertices, GLuint elementCount, GLuint groupCount);
		static GLuint CreateIndexBuffer(const GLuint& vao, const GLuint* indices, GLsizei elementCount);
		static void DeleteVertexBuffer(GLuint& vbo);
		static void DeleteIndexBuffer(GLuint& ibo);
		static void DeleteVertexArray(GLuint& vao);
	};
}
