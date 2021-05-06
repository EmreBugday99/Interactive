#pragma once
#include <vector>
#include <glad/glad.h>

class IndexBuffer;
class VertexBuffer;
class VertexArray
{
public:
	GLuint ArrayId;

	//TODO: MAKE THIS PRIVATE AND IMPLEMENT PUBLIC GETTER
	std::vector<VertexBuffer*> VertexBuffers;
	//TODO: MAKE THIS PRIVATE AND IMPLEMENT PUBLIC GETTER
	IndexBuffer* IBuffer;

	VertexArray();
	~VertexArray();

	VertexBuffer* CreateVertexBuffer(GLfloat* vertices, GLsizeiptr size);
	IndexBuffer* CreateIndexBuffer(GLuint* indices, GLsizeiptr indicesCount);
	void Bind();
	void Unbind();
	void Delete();
};
