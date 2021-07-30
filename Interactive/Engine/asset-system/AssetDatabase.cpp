#include "AssetDatabase.h"

AssetDatabase::AssetDatabase(Interactive* engine) : Engine(engine) {}

InteractiveObject* AssetDatabase::GetAsset(std::string assetId)
{
	return AssetMap[assetId];
}