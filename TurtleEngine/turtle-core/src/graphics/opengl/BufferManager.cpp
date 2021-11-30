#include "BufferManager.h"

namespace TurtleCore
{
	GLuint BufferManager::CreateVertexArray()
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);

		return vao;
	}

	GLuint BufferManager::CreateVertexBuffer(const GLuint& vao, const GLuint layoutIndex, const GLfloat* vertices, const GLuint elementCount, const GLuint groupCount)
	{
		GLuint vertexBufferId;
		glGenBuffers(1, &vertexBufferId);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

		// Setting buffer data
		const GLsizeiptr size = elementCount * sizeof(GLfloat);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(layoutIndex);
		glVertexAttribPointer(layoutIndex, groupCount, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		

		return vertexBufferId;
	}

	GLuint BufferManager::CreateIndexBuffer(const GLuint& vao, const GLuint* indices, const GLsizei elementCount)
	{
		GLuint ibo;
		glGenBuffers(1, &ibo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		// Setting buffer data
		const GLsizeiptr size = elementCount * sizeof(GLuint);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return ibo;
	}

	void BufferManager::DeleteVertexBuffer(GLuint& vbo)
	{
		glDeleteBuffers(1, &vbo);
		vbo = 0;
	}

	void BufferManager::DeleteIndexBuffer(GLuint& ibo)
	{
		glDeleteBuffers(1, &ibo);
		ibo = 0;
	}

	void BufferManager::DeleteVertexArray(GLuint& vao)
	{
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}
}