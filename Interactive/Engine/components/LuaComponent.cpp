#include "LuaComponent.h"
#include "../external/lua/src/lua.hpp"
#include "../external/lua/src/lstate.h"
#include "../reflection-system/ReflectionSystem.hpp"
#include "../script-system/LuaKeyMap.h"
#include "../utils/Utils.hpp"

std::map<lua_State*, LuaComponent*> LuaComponent::LuaComponents;

LuaComponent::LuaComponent(std::string scriptPath)
	: ScriptState(nullptr), ScriptPath(scriptPath)
{
	ScriptState = luaL_newstate();
	LuaComponents[ScriptState] = this;
	luaL_openlibs(ScriptState);

	ReflectionSystem::UpdateClassReflection<LuaComponent>(Reflection, "LuaComponent");
}

LuaComponent::~LuaComponent()
{
	lua_close(ScriptState);
	LuaComponents.erase(ScriptState);
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

	if (InputController->IsKeyPressed(Keys::B))
	{
		MarkForDestruction();
	}
}

void LuaComponent::Render() { Component::Render(); }

void LuaComponent::OnMarkedForDestruction() { Component::OnMarkedForDestruction(); }

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
	lua_pushcfunction(ScriptState, &CreateEntity);
	lua_setglobal(ScriptState, "CreateEntity");

	lua_pushcfunction(ScriptState, &GetEntity);
	lua_setglobal(ScriptState, "GetEntity");

	lua_pushcfunction(ScriptState, &HasComponent);
	lua_setglobal(ScriptState, "HasComponent");

	lua_pushcfunction(ScriptState, &Destroy);
	lua_setglobal(ScriptState, "Destroy");

	lua_pushcfunction(ScriptState, &CreateSprite);
	lua_setglobal(ScriptState, "CreateSprite");

	lua_pushcfunction(ScriptState, &IsKeyPressed);
	lua_setglobal(ScriptState, "IsKeyPressed");

	lua_pushcfunction(ScriptState, &GetTypeHash);
	lua_setglobal(ScriptState, "GetTypeHash");
}

int LuaComponent::CreateEntity(lua_State* state)
{
	LuaComponent* component = LuaComponents[state];

	Entity* entity = component->GetEnginePtr()->ECManager->CreateEntity(lua_tostring(state, -1));

	lua_pushlightuserdata(state, entity);

	return 1;
}

int LuaComponent::GetEntity(lua_State* state)
{
	LuaComponent* component = LuaComponents[state];

	lua_pushlightuserdata(state, component->Owner);
	std::cout << "Owner: " << component->Owner << std::endl;

	return 1;
}

int LuaComponent::HasComponent(lua_State* state)
{
	const char* typeName = lua_tostring(state, -1);
	Entity* entity = static_cast<Entity*>(lua_touserdata(state, -2));

	bool componentExists = entity->HasComponent(typeName);
	lua_pushboolean(state, componentExists);

	return 1;
}

int LuaComponent::GetComponent(lua_State* state)
{
	const char* typeName = lua_tostring(state, -1);
	Entity* entity = static_cast<Entity*>(lua_touserdata(state, -2));

	Component* component = entity->GetComponent(typeName);
	lua_pushlightuserdata(state, component);

	return 1;
}

int LuaComponent::Destroy(lua_State* state)
{
	InteractiveObject* object = static_cast<InteractiveObject*>(lua_touserdata(state, -1));
	object->MarkForDestruction();

	return 0;
}

int LuaComponent::CreateSprite(lua_State* state)
{
	Entity* entity = static_cast<Entity*>(lua_touserdata(state, -1));
	Sprite2D* sprite = entity->AddComponent<Sprite2D>();

	lua_pushlightuserdata(state, sprite);

	return 1;
}

int LuaComponent::IsKeyPressed(lua_State* state)
{
	const Keys checkedKey = LuaKeyMap::Keys[lua_tostring(state, -1)];
	const bool keyPressed = LuaComponents[state]->InputController->IsKeyPressed(checkedKey);

	lua_pushboolean(state, keyPressed);

	return 1;
}

int LuaComponent::GetTypeHash(lua_State* state)
{
	// I am storing the reflection's type hash's mother fucking memory address becuase LUA doesnt support unsigned types.
	// I AM AWARE THİS İS SOME FUCKED UP WORK AROUND DON'T FUCKING JUDGE. I WROTE THIS CODE AT 5 FUCKING AM
	Component* component = static_cast<Component*>(lua_touserdata(state, -1));
	lua_pushlightuserdata(state, &component->Reflection.GetTypeHashRef());

	//size_t& assads = *static_cast<size_t*>(lua_touserdata(state, -1));
	//std::cout << "Casted Native: " << assads << std::endl;
	//std::cout << "Native Native: " << component->Reflection.GetTypeHash() << std::endl;
	
	return 1;
}