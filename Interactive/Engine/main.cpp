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
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};

	Window* window = new Window("Test Window Interactive", 1920, 1080);

	ShaderProgram* shader1 = new ShaderProgram();
	shader1->AttachShader(ShaderTypes::VertexShader, "shader.vert");
	shader1->AttachShader(ShaderTypes::FragmentShader, "shader.frag");
	shader1->LinkProgram();

	VertexArray* vertexArray1 = new VertexArray();
	vertexArray1->CreateVertexBuffer(vertices, sizeof(vertices));
	vertexArray1->CreateIndexBuffer(indices, sizeof(indices));

	while (window->IsOpen() == false)
	{
		window->Clear();

		shader1->UseProgram();
		vertexArray1->Bind();
		vertexArray1->IBuffer->Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

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