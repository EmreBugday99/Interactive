#include <iostream>
#include "TestComponent.h"
#include "external/lua/src/lua.hpp"
#include "includes/CoreIncludes.h"

int main()
{
	Interactive* engine = new Interactive("Test Game Window");

	Entity* cameraEntity = engine->ECManager->CreateEntity("Camera Entity");
	Camera* cameraComp = cameraEntity->AddComponent<Camera>();
	engine->MainCamera = cameraComp;

	Entity* testEntity = engine->ECManager->CreateEntity("Test Entity");
	testEntity->AddComponent<Sprite2D>();
	testEntity->AddComponent<TestComponent>();

	lua_State* state = luaL_newstate();
	luaL_dostring(state, "num = 125");
	
	lua_getglobal(state, "num");
	int x = lua_tonumber(state, -1);
	std::cout << "Lua num: " << x << std::endl;
	
	lua_close(state);

	engine->Start();

	delete(engine);
	return 0;
}