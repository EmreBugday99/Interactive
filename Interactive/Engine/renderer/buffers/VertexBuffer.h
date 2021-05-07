#pragma once
#include <glad/glad.h>

class VertexBuffer
{
private:
	// Id of this buffer inside the graphics card
	GLuint BufferId;
	// How much memory is allocated for this buffer (in bytes)
	GLsizeiptr Size;
	// Amount of elements/vertices inside the buffer
	GLuint ElementCount;
	// Ex: 2 vec2's = 2 groups vs 1 vec4 = 1 group
	GLuint GroupCount;

public:
	VertexBuffer();
	~VertexBuffer();

	void SetBufferData(GLfloat* vertices, GLuint elementCount, GLuint groupCount);
	void Bind();
	void Unbind();
	void Delete();

	GLuint GetBufferId() const { return BufferId; }
	GLsizeiptr GetBufferSize() const { return Size; }
	GLuint GetElementCount() const { return ElementCount; }
	GLuint GetGroupCount() const { return GroupCount; }
};
