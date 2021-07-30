#pragma once
#include "../includes/CoreIncludes.h"

struct lua_State;
class LuaComponent : public Component
{
private:
	lua_State* ScriptState;
	std::string ScriptPath;

public:
	static std::map<lua_State*, LuaComponent*> LuaComponents;

public:
	LuaComponent(std::string scriptPath);
	~LuaComponent() override;

	void Initialize() override;
	void BeginPlay() override;
	void Update(float deltaTime) override;
	void Render() override;

	lua_State* GetScriptState() const { return ScriptState; }

protected:
	void OnMarkedForDestruction() override;

private:
	static Component* FactoryConstructor(std::map<std::string, void*>& dataMap);



	
	void PrepareLuaStack();

	////////////////////////////////////////
	// Native C Lua Bindings
	////////////////////////////////////////
	
	// CreateEntity(string(entity name))
	// is called with a string which defines the name of the new entity
	static int CreateEntity(lua_State* state);
	// GetEntity()
	// Lua: Called without any parameters. Simply returns the Entity this component is attached to.
	static int GetEntity(lua_State* state);
	// HasComponent(Entity*, string(typeName))
	// Called with two parameters.
	// Returns true if the provided entity has a component with the specified type.
	static int HasComponent(lua_State* state);
	// GetComponent(string(typeName))
	// Returns the pointer of the component with the specific type name.
	static int GetComponent(lua_State* state);
	// Destroy(InteractiveObject*(object inheriting from InteractiveObject))
	// Takes an InteractiveObject ptr as a parameter.
	// Simply marks that InteractiveObject for destruction. Returns nothing.
	static int Destroy(lua_State* state);
	// CreateSprite(Entity (entity the sprite component is going to be attached to))
	// Takes a parameter of an Entity. 
	static int CreateSprite(lua_State* state);
	// IsKeyPressed(string(string representation of a key defined in LuaKeyMap.h))
	// Cross references LuaKeyMap with Keys Enum and checks if that key is currently pressed.
	static int IsKeyPressed(lua_State* state);
	//HashString(string(string to hash))
	// Hashes the string provided by the lua function.
	static int GetTypeHash(lua_State* state);
};