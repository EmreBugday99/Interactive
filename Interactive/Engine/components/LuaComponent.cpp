#include "LuaComponent.h"

LuaComponent::LuaComponent(std::string scriptPath)
	: ScriptState(nullptr), ScriptPath(scriptPath)
{
	ScriptState = luaL_newstate();
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
}
void LuaComponent::BeginPlay()
{
	Component::BeginPlay();

	luaL_dofile(ScriptState, ScriptPath.c_str());
	lua_getglobal(ScriptState, "name");
	std::cout << "LuaComponent: " << lua_tostring(ScriptState, -1) << std::endl;
}
void LuaComponent::Update(float deltaTime) { Component::Update(deltaTime); }
void LuaComponent::Render() { Component::Render(); }
void LuaComponent::KeyboardCallback() { Component::KeyboardCallback(); }
void LuaComponent::OnMarkedForDestruction()
{
	Component::OnMarkedForDestruction();

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