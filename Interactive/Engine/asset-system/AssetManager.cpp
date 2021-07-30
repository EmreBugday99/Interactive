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

void AssetManager::CreateEntityAsset(std::string assetId, glm::vec3 entityPos, std::vector<std::string> components)
{
	using namespace std;
	// If Entity Asset Already Exists
		// Prepare the file for overriding
	std::string filePath = "assets/entities/" + assetId + ".entity";
	ofstream file(filePath);

	// Serialize the asset id
	file << R"(entityId = ")" << assetId << R"(")" << std::endl;

	//Serialize entity position
		// Serialize x position
	file << R"(posX = )" << entityPos.x << std::endl;
	// Serialize y position
	file << R"(posY = )" << entityPos.y << std::endl;
	// Serialize z position
	file << R"(posZ = )" << entityPos.z << std::endl;

	// Serialize Components
	file << "components = {";
	for (int i = 0; i < components.size(); ++i)
	{
		file << R"(")" << components[i] << R"(")";
		if (i != components.size() - 1)
			file << ", ";
	}
	file << "}" << std::endl;

	file.close();
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
			lua_getglobal(entityState, "posX");
			lua_getglobal(entityState, "posY");
			lua_getglobal(entityState, "posZ");
			lua_getglobal(entityState, "components");
			
			const char* entityId = lua_tostring(entityState, -5);
			float posX = lua_tonumber(entityState, -4);
			float posY = lua_tonumber(entityState, -3);
			float posZ = lua_tonumber(entityState, -2);
			
			std::vector<std::string> componentPaths;

			Entity* entity = Engine->ECManager->CreateEntity(entityId);
			Transform* transform = static_cast<Transform*>(entity->GetComponentComplex("Transform"));
			transform->Position.x = posX;
			transform->Position.y = posY;
			transform->Position.z = posZ;
			
			Database->AssetMap[entityId] = entity;

			////////////////////
			// Getting components from entity lua asset
			////////////////////

			
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