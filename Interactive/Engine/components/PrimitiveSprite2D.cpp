#include "PrimitiveSprite2D.h"
#include <iostream>
#include "Camera.h"
#include "../includes/CoreIncludes.h"

PrimitiveSprite2D::PrimitiveSprite2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)
	: Position(position), Size(size), Color(color)
{
	GLfloat vertices[] =
	{
		0,				0,				0,
		0,				size.y,			0,
		size.x,			size.y,			0,
		size.x,			0,				0
	};
	GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

	VAO = new VertexArray();
	VAO->CreateVertexBuffer(0, vertices, 3 * 4, 3);
	VAO->CreateIndexBuffer(indices, 6);

	Shader = new ShaderProgram();
	Shader->AttachShader(ShaderTypes::VertexShader, "shader.vert");
	Shader->AttachShader(ShaderTypes::FragmentShader, "shader.frag");
	Shader->LinkProgram();
}

PrimitiveSprite2D::~PrimitiveSprite2D()
{
	delete(VAO);
	VAO = nullptr;
}

void PrimitiveSprite2D::BeginPlay()
{
	InputController->BindKeyboardCallback(this);
}

void PrimitiveSprite2D::Update(float deltaTime)
{
	//Position.x += 0.002f;
	//Position.y += 0.002f;
}

void PrimitiveSprite2D::KeyboardCallback(Keys key, KeyActions actions)
{
	if (key == Keys::A && actions == KeyActions::PRESS)
	{
		std::cout << "A key is pressed!" << std::endl;
	}
}

void PrimitiveSprite2D::Render()
{
	if (Owner->Engine->MainCamera == nullptr)
		return;

	IndexBuffer* ibo = VAO->IBuffer;

	VAO->Bind();
	ibo->Bind();

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), Position);

	Shader->UseProgram();
	Shader->SetUniformData("model_mx", translationMatrix);
	Shader->SetUniformData("projection_mx", Owner->Engine->MainCamera->ProjectionMatrix);
	Shader->SetUniformData("componentColor", Color);
	glDrawElements(GL_TRIANGLES, ibo->GetElementCount(), GL_UNSIGNED_INT, nullptr);
	Shader->UnbindProgram();

	ibo->Unbind();
	VAO->Unbind();
}