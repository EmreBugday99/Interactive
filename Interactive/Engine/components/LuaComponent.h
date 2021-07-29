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
	static int IsKeyPressed(lua_State* state);
};