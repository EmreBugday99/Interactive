#pragma once
#include <vector>
#include <map>
#include "KeyActions.h"

enum class Keys;
class Component;
class Interactive;
class InputManager
{
public:
	Interactive* Engine;

	void BindKeyboardCallback(Component* callbackListener);
	void UnbindKeyboardCallback(Component* component);

	KeyActions GetKeyState(Keys key);
	bool IsKeyPressed(Keys key);
	bool IsKeyHold(Keys key);
	bool IsKeyReleased(Keys key);

	void ClearKeyStates();

private:
	friend struct GLFWwindow;
	friend class Interactive;

	KeyActions KeyBuffer[400] = { KeyActions::None };
	
	std::map<int, KeyActions> KeysActionsWaitingToBeCleaned;

	InputManager(Interactive* engine);
	
	static void KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
};
