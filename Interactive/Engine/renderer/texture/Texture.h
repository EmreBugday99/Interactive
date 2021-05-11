#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
public:
	std::string Path;
	GLuint TextureId;
	GLint Width;
	GLint Height;
	GLint BitDepth;
	GLint ActiveTextureId;
	
	void Bind();
	static void Unbind();

private:
	friend class TextureManager;

	Texture(std::string path);
	~Texture();

	void LoadTexture();
	void DeleteTexture();
};
