#pragma once
#include <map>
#include <vector>

class Component;
class InteractiveEngine;
class InputManager
{
public:
	InteractiveEngine* Engine;

	void BindKeyboardCallback(Component* callbackListener);
	//TODO: UnbindKeyboardCallback

private:
	friend struct GLFWwindow;
	friend class InteractiveEngine;

	std::vector<Component*> KeyboardCallbacksListeners;

	InputManager(InteractiveEngine* engine);
	
	static void KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
};
