#pragma once
#include "../includes/CoreIncludes.h"

struct lua_State;
class LuaComponent : public Component
{
private:
	lua_State* ScriptState;
	std::string ScriptPath;
	bool EnabledLuaKeyboardCallback;

public:
	LuaComponent(std::string scriptPath);

	void Initialize() override;
	void BeginPlay() override;
	void Update(float deltaTime) override;
	void Render() override;
	void KeyboardCallback() override;

	lua_State* GetScriptState() const { return ScriptState; }

protected:
	void OnMarkedForDestruction() override;

private:
	static Component* FactoryConstructor(std::map<std::string, void*>& dataMap);
	
	static LuaComponent* GetClassPointerFromLuaStack(lua_State* state);
	void PrepareLuaStack();
	static int EnableKeyboardCallback(lua_State* state);
};