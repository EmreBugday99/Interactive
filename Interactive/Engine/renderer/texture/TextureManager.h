#pragma once
#include <map>
#include <string>
#include <glad/glad.h>

class Interactive;
class Texture;
class TextureManager
{
public:
	std::map<std::string, Texture*> Textures;
	Interactive* Engine;

	GLint MaxTextureCap;

	TextureManager(Interactive* engine);
	~TextureManager();
	
	Texture* CreateTexture(std::string textureName, std::string texturePath);
};
