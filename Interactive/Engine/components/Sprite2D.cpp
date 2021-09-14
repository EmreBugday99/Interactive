#include "Sprite2D.h"
#include <iostream>
#include "Camera.h"
#include "Transform.h"
#include "../includes/CoreIncludes.h"
#include "../reflection-system/ReflectionSystem.hpp"

Sprite2D::Sprite2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)
	: Color(color), Shader(nullptr), VAO(nullptr), AttachedTexture(nullptr)
{
	ReflectionSystem::AddInheritedClass<Sprite2D>(Reflection, "Sprite2D");
}

Sprite2D::Sprite2D()
{
	AttachedTexture = nullptr;
	Shader = nullptr;
	VAO = nullptr;

	Color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	ReflectionSystem::AddInheritedClass<Sprite2D>(Reflection, "Sprite2D");
	ReflectionSystem::UpdateClassReflection<Sprite2D>(Reflection, "Sprite2D");
}

Sprite2D::~Sprite2D() {}

void Sprite2D::Initialize()
{
	Component::Initialize();

	CreateSprite2D();

	Shader = new ShaderProgram();
	Shader->AttachShader(ShaderTypes::VertexShader, "shaders/shader.vert");
	Shader->AttachShader(ShaderTypes::FragmentShader, "shaders/basicShader.frag");

	Shader->LinkProgram();
}
void Sprite2D::Update(float deltaTime) { Component::Update(deltaTime); }

void Sprite2D::CreateSprite2D()
{
	GLfloat vertices[] =
	{
		0,									0,									0,
		0,									GetTransform()->GetSize().y,		0,
		GetTransform()->GetSize().x,		GetTransform()->GetSize().y,		0,
		GetTransform()->GetSize().x,		0,									0
	};
	GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

	if (VAO == nullptr)
		VAO = new VertexArray();
	VAO->CreateVertexBuffer(0, vertices, 3 * 4, 3);
	VAO->CreateIndexBuffer(indices, 6);
}

void Sprite2D::UpdateSprite()
{
	std::cout << "Transform X: " << GetTransform()->GetSize().x;

	GLfloat vertices[] =
	{
		0,									0,									0,
		0,									GetTransform()->GetSize().y,		0,
		GetTransform()->GetSize().x,		GetTransform()->GetSize().y,		0,
		GetTransform()->GetSize().x,		0,									0
	};
	VAO->VertexBuffers[0]->Bind();
	VAO->VertexBuffers[0]->SetBufferData(vertices, 3 * 4, 3);
	VAO->VertexBuffers[0]->Unbind();
}

void Sprite2D::Render()
{
	Component::Render();

	if (Owner->GetEnginePtr()->MainCamera == nullptr)
		return;

	IndexBuffer* ibo = VAO->IBuffer;

	VAO->Bind();
	ibo->Bind();

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), GetTransform()->Position);

	Shader->UseProgram();
	Shader->SetUniformData("model_mx", translationMatrix);
	Shader->SetUniformData("projection_mx", Owner->GetEnginePtr()->MainCamera->ProjectionMatrix);

	if (AttachedTexture != nullptr)
	{
		AttachedTexture->Bind();
		GLint activeTextureId = 0;
		Shader->SetUniformData("activeTextureId", AttachedTexture->ActiveTextureId);
	}
	else
	{
		Shader->SetUniformData("componentColor", Color);
	}
	glDrawElements(GL_TRIANGLES, ibo->GetElementCount(), GL_UNSIGNED_INT, nullptr);
	Shader->UnbindProgram();

	Texture::Unbind();
	ibo->Unbind();
	VAO->Unbind();
}

void Sprite2D::AttachTexture(Texture* textureToAttach)
{
	GLfloat textureCoords[] =
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	VAO->CreateVertexBuffer(1, textureCoords, 2 * 4, 2);

	Shader->DeleteProgram();
	Shader->CreateShader();
	AttachedTexture = textureToAttach;
	Shader->AttachShader(ShaderTypes::VertexShader, "shaders/shader.vert");
	Shader->AttachShader(ShaderTypes::FragmentShader, "shaders/textureShader.frag");
	Shader->LinkProgram();
}

void Sprite2D::BeginPlay()
{
	std::cout << "I am alive!" << std::endl;
}

void Sprite2D::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

	Shader->DeleteProgram();
	delete(Shader);
	Shader = nullptr;
	delete(VAO);
	VAO = nullptr;
}