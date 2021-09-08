#include "AssetManager.h"
#include <fstream>
#include <filesystem>

#include "AssetDatabase.h"
#include "../includes/CoreIncludes.h"
#include "../external/lua/src/lua.hpp"

AssetManager::AssetManager(Interactive* engine)
	: Engine(engine), InitializedDatabase(false)
{
	Database = new AssetDatabase(engine);
}

void AssetManager::InitializeDatabase()
{
	namespace fs = std::filesystem;

	if (InitializedDatabase)
		return;

	const char* path = "/assets/";

	for (auto& file : fs::recursive_directory_iterator(path))
	{
		if (file.path().extension().string() == ".entity")
			LoadEntityAsset(file.path().extension().string().c_str());
		else if (file.path().extension().string() == ".scene")
			LoadSceneAsset(file.path().extension().string().c_str());
	}

	InitializedDatabase = true;
}

Entity* AssetManager::LoadEntityAsset(const char* assetPath)
{
	lua_State* state = luaL_newstate();
	luaL_dofile(state, assetPath);

	lua_getglobal(state, "entityId"); // -5
	lua_getglobal(state, "posX"); // -4
	lua_getglobal(state, "posY"); // -3
	lua_getglobal(state, "posZ"); // -2
	lua_getglobal(state, "components"); // -1

	const char* entityId = lua_tostring(state, -5);
	float posX = lua_tonumber(state, -4);
	float posY = lua_tonumber(state, -3);
	float posZ = lua_tonumber(state, -2);

	Entity* entity = Engine->ECManager->CreateEntity(entityId, Engine->SceneSystem->ActiveScene);
	Transform* transform = reinterpret_cast<Transform*>(entity->GetComponentComplex("Transform"));

	transform->Position.x = posX;
	transform->Position.y = posY;
	transform->Position.z = posZ;

	Database->AssetMap[entityId] = entity;

	////////////////////
	// Getting components from entity lua asset
	////////////////////

	std::vector<std::string> componentPaths;
	// key is nil as we don't know the key
	lua_pushnil(state);
	// 'components' stack index became -2 as we pushed nil to the stack.
	while (lua_next(state, -2))
	{
		const char* componentPath = lua_tostring(state, -1);
		componentPaths.emplace_back(componentPath);
		entity->AddComponent<LuaComponent>(componentPath);

		// lua_next is going to push the value to the stack,
		// so we need to pop it.
		lua_pop(state, 1);
	}

	// popping key(nil) from the stack.
	lua_pop(state, 1);
	// After this point,
	// our stack should be the same as before we traversed the table.

	return entity;
}

Scene* AssetManager::LoadSceneAsset(const char* assetPath)
{
	lua_State* state = luaL_newstate();
	luaL_dofile(state, assetPath);

	lua_getglobal(state, "entityId"); // -2
	lua_getglobal(state, "entities"); // -1

	const char* SceneName = lua_tostring(state, -2);
	Scene* scene = Engine->SceneSystem->CreateEmptyScene(SceneName);

	////////////////////
	// Getting entities from scene lua asset
	////////////////////

	std::vector<std::string> entityPaths;
	// key is nil as we don't know the key
	lua_pushnil(state);
	// 'entities' stack index became -2 as we pushed nil to the stack.
	while (lua_next(state, -2))
	{
		const char* entityPath = lua_tostring(state, -1);
		entityPaths.emplace_back(entityPath);

		// lua_next is going to push the value to the stack,
		// so we need to pop it.
		lua_pop(state, 1);

		LoadEntityAsset(entityPath);
	}

	// popping key(nil) from the stack.
	lua_pop(state, 1);
	// After this point,
	// our stack should be the same as before we traversed the table.

	return scene;
}