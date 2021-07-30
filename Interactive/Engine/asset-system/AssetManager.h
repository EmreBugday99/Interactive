#pragma once
#include <string>
#include <vector>
#include <glm/vec3.hpp>
class AssetDatabase;
class Interactive;

class AssetManager
{
private:
	Interactive* Engine;

public:
	AssetDatabase* Database;

public:
	AssetManager(Interactive* engine);

	void InitializeDatabase();
	void CreateEntityAsset(std::string assetId, glm::vec3 entityPos, std::vector<std::string> components);

private:
	void InitializeEntityAssets();
};
