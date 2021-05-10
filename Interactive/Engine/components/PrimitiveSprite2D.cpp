#include "PrimitiveSprite2D.h"
#include <iostream>
#include "Camera.h"
#include "../includes/CoreIncludes.h"

PrimitiveSprite2D::PrimitiveSprite2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)
	: Position(position), Size(size), Color(color), Shader(nullptr), VAO(nullptr)
{
	CreateSprite2D();
}

PrimitiveSprite2D::PrimitiveSprite2D()
{
	Shader = nullptr;
	VAO = nullptr;

	Position = glm::vec3(0.5f, 0.8f, 0.0f);
	Size = glm::vec2(0.1f, 0.1f);
	Color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	CreateSprite2D();
}

PrimitiveSprite2D::~PrimitiveSprite2D()
{
	delete(VAO);
	VAO = nullptr;
}

void PrimitiveSprite2D::CreateSprite2D()
{
	GLfloat vertices[] =
	{
		0,				0,				0,
		0,				Size.y,			0,
		Size.x,			Size.y,			0,
		Size.x,			0,				0
	};
	GLuint indices[] = { 0, 1, 2, 2, 3, 0 };
	GLfloat textureCoords[] = 
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	VAO = new VertexArray();
	VAO->CreateVertexBuffer(0, vertices, 3 * 4, 3);
	VAO->CreateIndexBuffer(indices, 6);
	VAO->CreateVertexBuffer(1, textureCoords, 2 * 4, 2);

	Shader = new ShaderProgram();
	Shader->AttachShader(ShaderTypes::VertexShader, "shader.vert");
	Shader->AttachShader(ShaderTypes::FragmentShader, "shader.frag");
	Shader->LinkProgram();
}

void PrimitiveSprite2D::BeginPlay()
{
	InputController->BindKeyboardCallback(this);
	TestTexture = Engine->TextureSystem->CreateTexture("testTexture2", "test.jpg");
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

	Engine->TextureSystem->Textures["testTexture2"]->Bind();
	VAO->Bind();
	ibo->Bind();

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), Position);

	Shader->UseProgram();
	Shader->SetUniformData("model_mx", translationMatrix);
	Shader->SetUniformData("projection_mx", Owner->Engine->MainCamera->ProjectionMatrix);
	//Shader->SetUniformData("componentColor", Color);
	GLint a = 0;
	Shader->SetUniformData("texture0", a);
	glDrawElements(GL_TRIANGLES, ibo->GetElementCount(), GL_UNSIGNED_INT, nullptr);
	Shader->UnbindProgram();

	ibo->Unbind();
	VAO->Unbind();
}