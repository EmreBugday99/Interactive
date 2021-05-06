#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	BufferId = 0;
	VerticesSize = 0;
	
	glGenBuffers(1, &BufferId);
}

VertexBuffer::~VertexBuffer()
{
	Delete();
}

void VertexBuffer::SetBufferData(GLfloat* vertices, GLsizeiptr size, GLuint index)
{
	Bind();
	
	VerticesSize = size;
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(index);
	
	Unbind();
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