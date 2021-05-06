#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
	BufferId = 0;
	IndicesCount = 0;

	glGenBuffers(1, &BufferId);
}

IndexBuffer::~IndexBuffer()
{
	Delete();
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetBufferData(GLuint* indices, GLsizeiptr indicesCount)
{
	Bind();

	IndicesCount = indicesCount;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount, indices, GL_STATIC_DRAW);

	Unbind();
}

void IndexBuffer::Delete()
{
	if (BufferId == 0)
		return;

	glDeleteBuffers(1, &BufferId);
	BufferId = 0;
}