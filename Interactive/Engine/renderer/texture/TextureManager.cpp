#include "TextureManager.h"

#include <iostream>

#include "Texture.h"

TextureManager::TextureManager()
{
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MaxTextureCap);
	std::cout << "[OpenGL] Max Texture Count: " << MaxTextureCap << std::endl;
}

TextureManager::~TextureManager() {}

Texture* TextureManager::CreateTexture(std::string textureName, std::string texturePath)
{

	auto mapIterator = Textures.find(textureName);
	if (mapIterator != Textures.end())
	{
		std::cout << "Another texture already exists with that name!" << std::endl;
		return nullptr;
	}
	
	Texture* newTexture = new Texture(texturePath, textureName);
	Textures[textureName] = newTexture;

	return newTexture;
}