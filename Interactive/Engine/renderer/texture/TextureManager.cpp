#include "TextureManager.h"

#include <iostream>

#include "Texture.h"

TextureManager::TextureManager(InteractiveEngine* engine)
	: Engine(engine) {}

TextureManager::~TextureManager() {}

Texture* TextureManager::CreateTexture(std::string textureName, std::string texturePath)
{
	Texture* newTexture = new Texture(texturePath);

	auto mapIterator = Textures.find(textureName);
	if (mapIterator == Textures.end())
	{
		std::cout << "Another texture already exists with that name! Deleting old one..." << std::endl;
		delete(Textures[textureName]);
		Textures[textureName] = nullptr;
	}

	Textures[textureName] = newTexture;

	return newTexture;
}