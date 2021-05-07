#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
	ArrayId = 0;
	IBuffer = nullptr;

	glGenVertexArrays(1, &ArrayId);
}

VertexArray::~VertexArray()
{
	// Destructing VertexArray will initiate a chain reaction of all VBOs & IBO to be destructed as well.
	Delete();
}

VertexBuffer* VertexArray::CreateVertexBuffer(GLuint layoutIndex, GLfloat* vertices, GLuint elementCount, GLuint groupCount)
{
	VertexBuffer* vertexBuffer = new VertexBuffer();
	VertexBuffers.push_back(vertexBuffer);

	Bind();
	vertexBuffer->Bind();

	vertexBuffer->SetBufferData(vertices, elementCount, groupCount);
	glEnableVertexAttribArray(layoutIndex);
	glVertexAttribPointer(layoutIndex, groupCount, GL_FLOAT, GL_FALSE, 0, 0);
	
	vertexBuffer->Unbind();
	Unbind();

	return vertexBuffer;
}

IndexBuffer* VertexArray::CreateIndexBuffer(GLuint* indices, GLsizeiptr indicesCount)
{
	// TODO: Throw error when error handling is implemented!
	// If we already have an Index Buffer, creating a new one will result in memory leak.
	if (IBuffer != nullptr)
		return IBuffer;

	Bind();

	IBuffer = new IndexBuffer();
	IBuffer->SetBufferData(indices, indicesCount);

	Unbind();

	return IBuffer;
}

void VertexArray::Bind()
{
	glBindVertexArray(ArrayId);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::Delete()
{
	if (ArrayId == 0)
		return;

	for (VertexBuffer* vbo : VertexBuffers)
	{
		if (vbo == nullptr) continue;
		delete(vbo);
	}
	VertexBuffers.clear();

	delete(IBuffer);

	glDeleteVertexArrays(1, &ArrayId);
	ArrayId = 0;
}