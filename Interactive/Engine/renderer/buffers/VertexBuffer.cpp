#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	BufferId = 0;
	Size = 0;
	ElementCount = 0;
	GroupCount = 0;

	glGenBuffers(1, &BufferId);
}

VertexBuffer::~VertexBuffer()
{
	Delete();
}

void VertexBuffer::SetBufferData(GLfloat* vertices, GLuint elementCount, GLuint groupCount)
{
	Size = elementCount * sizeof(GLfloat);
	ElementCount = elementCount;
	GroupCount = groupCount;

	glBufferData(GL_ARRAY_BUFFER, Size, vertices, GL_STATIC_DRAW);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, BufferId);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete()
{
	if (BufferId == 0)
		return;

	glDeleteBuffers(1, &BufferId);
	BufferId = 0;
}