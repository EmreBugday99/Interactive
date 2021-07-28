#pragma once
#include <string>
#include <vector>
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
	void CreateEntityAsset(std::string assetId, std::vector<std::string> components);

private:
	void InitializeEntityAssets();
};
