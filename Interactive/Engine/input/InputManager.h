#pragma once
#include <map>
#include <vector>

#include "KeyActions.h"

enum class Keys;
class Component;
class InteractiveEngine;
class InputManager
{
public:
	InteractiveEngine* Engine;

	void BindKeyboardCallback(Component* callbackListener);
	//TODO: UnbindKeyboardCallback

	KeyActions GetKeyState(Keys key);

private:
	friend struct GLFWwindow;
	friend class InteractiveEngine;

	KeyActions KeyBuffer[400] = { KeyActions::NotPressed };

	std::vector<Component*> KeyboardCallbacksListeners;

	InputManager(InteractiveEngine* engine);
	
	static void KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
};
