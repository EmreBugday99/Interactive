#include "PrimitiveSprite2D.h"
#include <iostream>
#include "Camera.h"
#include "../includes/CoreIncludes.h"

PrimitiveSprite2D::PrimitiveSprite2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)
	: Position(position), Size(size), Color(color), Shader(nullptr), VAO(nullptr), AttachedTexture(nullptr)
{
}

PrimitiveSprite2D::PrimitiveSprite2D()
{
	Shader = nullptr;
	VAO = nullptr;

	Position = glm::vec3(0.5f, 0.8f, 0.0f);
	Size = glm::vec2(50.0f, 50.0f);
	Color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
}

PrimitiveSprite2D::~PrimitiveSprite2D()
{
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

	VAO = new VertexArray();
	VAO->CreateVertexBuffer(0, vertices, 3 * 4, 3);
	VAO->CreateIndexBuffer(indices, 6);
}

void PrimitiveSprite2D::BeginPlay()
{
	Component::BeginPlay();

	CreateSprite2D();

	Shader = new ShaderProgram();
	Shader->AttachShader(ShaderTypes::VertexShader, "shaders/shader.vert");
	Shader->AttachShader(ShaderTypes::FragmentShader, "shaders/basicShader.frag");

	Shader->LinkProgram();
}

void PrimitiveSprite2D::Update(float deltaTime)
{
	Component::Update(deltaTime);
}

void PrimitiveSprite2D::KeyboardCallback()
{
	Component::KeyboardCallback();
}

void PrimitiveSprite2D::Render()
{
	Component::Render();

	if (Owner->GetEnginePtr()->MainCamera == nullptr)
		return;

	IndexBuffer* ibo = VAO->IBuffer;

	VAO->Bind();
	ibo->Bind();

	//TODO: Remove it from here when Transform component is implemented.
	//TODO: SetSize(glm::vec3 newSize) function of the Transform component should call this function.
	UpdateRenderSize();

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), Position);

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

void PrimitiveSprite2D::AttachTexture(Texture* textureToAttach)
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

void PrimitiveSprite2D::UpdateRenderSize()
{
	GLfloat vertices[] =
	{
		0,				0,				0,
		0,				Size.y,			0,
		Size.x,			Size.y,			0,
		Size.x,			0,				0
	};
	VAO->VertexBuffers[0]->Bind();
	VAO->VertexBuffers[0]->SetBufferData(vertices, 3 * 4, 3);
	VAO->VertexBuffers[0]->Unbind();
}

void PrimitiveSprite2D::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

	Shader->DeleteProgram();
	delete(Shader);
	Shader = nullptr;
	delete(VAO);
	VAO = nullptr;
}