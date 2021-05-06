#pragma once
#include <glad/glad.h>

class IndexBuffer
{
public:
	//TODO: MAKE THIS PRIVATE AND IMPLEMENT PUBLIC GETTER
	GLuint BufferId;
	//TODO: MAKE THIS PRIVATE AND IMPLEMENT PUBLIC GETTER
	GLsizeiptr IndicesCount;

	IndexBuffer();
	~IndexBuffer();

	void Bind();
	void Unbind();
	void SetBufferData(GLuint* indices, GLsizeiptr indicesCount);
	void Delete();
};
