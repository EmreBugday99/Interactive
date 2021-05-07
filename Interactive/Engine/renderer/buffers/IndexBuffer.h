#pragma once
#include <glad/glad.h>

class IndexBuffer
{
private:
	// Id of this buffer inside the graphics card
	GLuint BufferId;
	// How much memory is allocated for this buffer (in bytes)
	GLsizeiptr Size;
	// Amount of elements/vertices inside the buffer
	GLuint ElementCount;

public:
	IndexBuffer();
	~IndexBuffer();

	void Bind();
	void Unbind();
	void SetBufferData(GLuint* indices, GLuint elementCount);
	void Delete();

	GLuint GetBufferId() const { return BufferId; }
	GLsizeiptr GetSize() const { return Size; }
	GLuint GetElementCount() const { return ElementCount; }
};
