#include "LuaComponent.h"
#include "../external/lua/src/lua.hpp"
#include "../external/lua/src/lstate.h"
#include "../script-system/LuaKeyMap.h"

std::map<lua_State*, LuaComponent*> LuaComponent::LuaComponents;

LuaComponent::LuaComponent(std::string scriptPath)
	: ScriptState(nullptr), ScriptPath(scriptPath)
{
	ScriptState = luaL_newstate();

	LuaComponents[ScriptState] = this;

	luaL_openlibs(ScriptState);
}

void LuaComponent::Initialize()
{
	Component::Initialize();

	// If not already registered, register the factory constructor to the map
	if (ComponentFactory::ConstructorMap.find("LuaComponent") == ComponentFactory::ConstructorMap.end())
	{
		ComponentFactory::ConstructorMap["LuaComponent"] = &FactoryConstructor;
		std::cout << "[Component Factory] LuaComponent Factory Constructor initialized!" << std::endl;
	}

	PrepareLuaStack();
	luaL_dofile(ScriptState, ScriptPath.c_str());
}

void LuaComponent::BeginPlay()
{
	Component::BeginPlay();

	lua_getglobal(ScriptState, "BeginPlay");
	if (!lua_isfunction(ScriptState, -1))
		std::cout << "[ScriptSystem] Lua Script needs a function called BeginPlay " << ScriptPath << std::endl;

	lua_pcall(ScriptState, 0, 0, 0);
}

void LuaComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	lua_getglobal(ScriptState, "Update");
	if (!lua_isfunction(ScriptState, -1))
		std::cout << "[ScriptSystem] Lua Script needs a function called Update(deltaTime)" << ScriptPath << std::endl;

	const int args = 1;
	const int returns = 0;

	lua_pushnumber(ScriptState, deltaTime);
	lua_pcall(ScriptState, args, returns, 0);
}

void LuaComponent::Render() { Component::Render(); }

void LuaComponent::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

	LuaComponents.erase(ScriptState);
	lua_close(ScriptState);
}

Component* LuaComponent::FactoryConstructor(std::map<std::string, void*>& dataMap)
{
	std::string path = *static_cast<std::string*>(dataMap["path"]);
	Entity* entity = static_cast<Entity*>(dataMap["entity"]);

	//LuaComponent* component = entity->AddComponent<LuaComponent>(path.c_str());

	delete static_cast<std::string*>(dataMap["path"]);
	dataMap["path"] = nullptr;
	delete static_cast<Entity*>(dataMap["entity"]);
	dataMap["entity"] = nullptr;

	return nullptr;
}

void LuaComponent::PrepareLuaStack()
{
	lua_pushcfunction(ScriptState, &IsKeyPressed);
	lua_setglobal(ScriptState, "IsKeyPressed");
}

int LuaComponent::IsKeyPressed(lua_State* state)
{
	const Keys checkedKey = LuaKeyMap::Keys[lua_tostring(state, -1)];
	const bool keyPressed = LuaComponents[state]->InputController->IsKeyPressed(checkedKey);

	lua_pushboolean(state, keyPressed);

	return 1;
}