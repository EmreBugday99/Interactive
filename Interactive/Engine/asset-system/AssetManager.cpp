#include "AssetManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "../includes/CoreIncludes.h"
#include "../external/lua/src/lua.hpp"

AssetManager::AssetManager(Interactive* engine)
	: Engine(engine)
{
	Database = new AssetDatabase(engine);
}

void AssetManager::InitializeDatabase()
{
	InitializeEntityAssets();
}

void AssetManager::CreateEntityAsset(std::string assetId, std::vector<std::string> components)
{
}

void AssetManager::InitializeEntityAssets()
{
	namespace fs = std::filesystem;

	std::string path = "assets/";
	std::string extension = ".entity";

	std::cout << "\n[Asset System] Creating Entities...\n" << std::endl;

	for (auto& p : fs::recursive_directory_iterator(path))
	{
		if (p.path().extension() == extension)
		{
			std::string rawAssetData;

			lua_State* entityState = luaL_newstate();
			luaL_dofile(entityState, p.path().string().c_str());

			lua_getglobal(entityState, "entityId");
			if (!lua_isstring(entityState, -1))
				std::cout << "[AssetSystem] ERROR! entityId must be a string! :" << p.path().string() << std::endl;

			const char* entityId = lua_tostring(entityState, -1);
			std::vector<std::string> componentPaths;

			Entity* entity = Engine->ECManager->CreateEntity(entityId);
			Database->AssetMap[entityId] = entity;

			////////////////////
			// Getting components from entity lua asset
			////////////////////

			lua_getglobal(entityState, "components");
			if (!lua_istable(entityState, -1))
				std::cout << "[AssetSystem] ERROR! components must be a table of strings! :" << p.path().string() << std::endl;

			// key is nil as we don't know the key
			lua_pushnil(entityState);
			// 'components' stack index became -2 as we pushed nil to the stack.
			while (lua_next(entityState, -2))
			{
				if (!lua_isstring(entityState, -1))
					std::cout << "[AssetSystem] ERROR! all elements in components table must be a string! :" << p.path().string() << std::endl;
				
				std::string componentPath = lua_tostring(entityState, -1);
				componentPaths.emplace_back(componentPath);
				entity->AddComponent<LuaComponent>(componentPath);

				// lua_next is going to push the value to the stack,
				// so we need to pop it.
				lua_pop(entityState, 1);
			}
			// popping key(nil) from the stack.
			lua_pop(entityState, 1);
			// After this point,
			// our stack should be the same as before we traversed the table.

			std::cout << "[Asset System] Created Entity: " << p.path() << std::endl;

			lua_close(entityState);
		}
	}

	std::cout << "\n[Asset System] Finished Creating Entities.\n" << std::endl;
}