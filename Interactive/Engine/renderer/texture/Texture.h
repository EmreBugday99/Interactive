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

	std::string GetTextureName() const { return TextureName; }

private:
	friend class TextureManager;

	std::string TextureName;

	Texture(std::string path, std::string textureName);
	~Texture();

	void LoadTexture();
	void DeleteTexture();
};
