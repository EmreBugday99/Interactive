#pragma once
#include <vector>
#include <glad/glad.h>

class IndexBuffer;
class VertexBuffer;
class VertexArray
{
public:
	// Id of array buffer inside the graphics card
	GLuint ArrayId;
	// VBOs this VAO is responsible for maintaining
	std::vector<VertexBuffer*> VertexBuffers;
	IndexBuffer* IBuffer;

public:
	VertexArray();
	~VertexArray();

	VertexBuffer* CreateVertexBuffer(GLuint layoutIndex, GLfloat* vertices, GLuint elementCount, GLuint groupCount);
	IndexBuffer* CreateIndexBuffer(GLuint* indices, GLuint elementCount);
	void Bind();
	void Unbind();
	void Delete();
};
