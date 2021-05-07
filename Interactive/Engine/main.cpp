#include <iostream>
#include "renderer/Window.h"
#include "renderer/buffers/IndexBuffer.h"
#include "renderer/buffers/VertexArray.h"
#include "renderer/shader/ShaderProgram.h"

int main()
{
	std::cout << "Hello World!" << std::endl;

	GLfloat vertices[] =
	{
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	Window* window = new Window("Test Window Interactive", 1920, 1080);

	ShaderProgram* shader1 = new ShaderProgram();
	shader1->AttachShader(ShaderTypes::VertexShader, "shader.vert");
	shader1->AttachShader(ShaderTypes::FragmentShader, "shader.frag");
	shader1->LinkProgram();

	VertexArray* vertexArray1 = new VertexArray();
	VertexBuffer* vbo1 = vertexArray1->CreateVertexBuffer(0, vertices, 12, 3);
	IndexBuffer* ibo1 = vertexArray1->CreateIndexBuffer(indices, 6);

	while (window->IsOpen() == false)
	{
		window->Clear();

		shader1->UseProgram();
		vertexArray1->Bind();
		vertexArray1->IBuffer->Bind();

		glDrawElements(GL_TRIANGLES, ibo1->GetElementCount(), GL_UNSIGNED_INT, 0);

		vertexArray1->Unbind();
		vertexArray1->IBuffer->Unbind();

		window->Update();
	}

	delete(window);
	delete(vertexArray1);
	delete(shader1);
	glfwTerminate();

	return 0;
}