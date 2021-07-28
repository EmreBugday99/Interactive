#pragma once
#include "../external/lua/src/lua.hpp"
#include "../includes/CoreIncludes.h"

class LuaComponent : public Component
{
private:
	lua_State* ScriptState;
	std::string ScriptPath;

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
};