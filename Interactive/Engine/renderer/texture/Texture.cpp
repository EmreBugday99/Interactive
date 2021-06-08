#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>

Texture::Texture(std::string path, std::string textureName)
	: Path(path), TextureId(0), Width(0), Height(0), BitDepth(0), ActiveTextureId(0), TextureName(textureName)
{
	stbi_set_flip_vertically_on_load(true);
	
	std::cout << "Constructing new texture" << std::endl;
	
	GLubyte* pixelBytes = stbi_load(path.c_str(), &Width, &Height, &BitDepth, STBI_rgb_alpha);
	glGenTextures(1, &TextureId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelBytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(pixelBytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	DeleteTexture();
}

void Texture::LoadTexture()
{
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, TextureId);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::DeleteTexture()
{
	glDeleteTextures(1, &TextureId);
}