#pragma once
#include <map>
#include <string>
#include <glad/glad.h>

class Texture;
class TextureManager
{
public:
	std::map<std::string, Texture*> Textures;

	GLint MaxTextureCap;

	TextureManager();
	~TextureManager();
	
	Texture* CreateTexture(std::string textureName, std::string texturePath);
};
