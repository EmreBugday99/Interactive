#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
	//TODO: MAKE THIS PRIVATE AND IMPLEMENT PUBLIC GETTER
	GLuint BufferId;
	//TODO: MAKE THIS PRIVATE AND IMPLEMENT PUBLIC GETTER
	GLsizeiptr VerticesSize;

public:
	VertexBuffer();
	~VertexBuffer();

	void SetBufferData(GLfloat* vertices, GLsizeiptr size, GLuint index);
	void Bind();
	void Unbind();
	void Delete();
};
