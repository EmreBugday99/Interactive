#pragma once
#include <map>
#include <vector>

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

private:
	friend struct GLFWwindow;
	friend class Interactive;

	KeyActions KeyBuffer[400] = { KeyActions::NotPressed };

	std::vector<Component*> KeyboardCallbacksListeners;

	InputManager(Interactive* engine);
	
	static void KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
};
