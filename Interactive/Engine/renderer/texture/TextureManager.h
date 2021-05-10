#pragma once
#include <map>
#include <string>

class InteractiveEngine;
class Texture;
class TextureManager
{
public:
	std::map<std::string, Texture*> Textures;
	InteractiveEngine* Engine;

	TextureManager(InteractiveEngine* engine);
	~TextureManager();
	
	Texture* CreateTexture(std::string textureName, std::string texturePath);
};
