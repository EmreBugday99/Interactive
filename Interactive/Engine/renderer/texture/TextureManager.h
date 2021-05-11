#pragma once
#include <map>
#include <string>
#include <glad/glad.h>

class InteractiveEngine;
class Texture;
class TextureManager
{
public:
	std::map<std::string, Texture*> Textures;
	InteractiveEngine* Engine;

	GLint MaxTextureCap;

	TextureManager(InteractiveEngine* engine);
	~TextureManager();
	
	Texture* CreateTexture(std::string textureName, std::string texturePath);
};
