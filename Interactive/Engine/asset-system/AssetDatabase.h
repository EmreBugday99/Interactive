#pragma once
#include <map>
#include <string>

class InteractiveObject;
class Interactive;

class AssetDatabase
{
public:
	Interactive* Engine;

	AssetDatabase(Interactive* engine);

	InteractiveObject* GetAsset(std::string assetId);

private:
	friend class AssetManager;
	std::map<std::string, InteractiveObject*> AssetMap;
};
