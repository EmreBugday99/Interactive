#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
	ArrayId = 0;
	IBuffer = nullptr;

	// 1st for coord layout, 2nd for texture layout
	VertexBuffers = std::vector<VertexBuffer*>();
	
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

IndexBuffer* VertexArray::CreateIndexBuffer(GLuint* indices, GLuint elementCount)
{
	// TODO: Throw error when error handling is implemented!
	// If we already have an Index Buffer, creating a new one will result in memory leak.
	if (IBuffer != nullptr)
		return IBuffer;
	IBuffer = new IndexBuffer();

	Bind();
	IBuffer->Bind();
	IBuffer->SetBufferData(indices, elementCount);

	IBuffer->Unbind();
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
		delete(vbo);
		vbo = nullptr;
	}
	VertexBuffers.clear();

	delete(IBuffer);
	IBuffer = nullptr;

	glDeleteVertexArrays(1, &ArrayId);
	ArrayId = 0;
}