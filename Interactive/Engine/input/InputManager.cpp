#include "InputManager.h"

#include <iostream>

#include "../includes/CoreIncludes.h"

InputManager::InputManager(Interactive* engine) : Engine(engine)
{
	glfwSetWindowUserPointer(Engine->GameWindow->GetGlfwWindow(), Engine);
	glfwSetKeyCallback(Engine->GameWindow->GetGlfwWindow(), KeyboardCallback);
}

void InputManager::BindKeyboardCallback(Component* callbackListener)
{
	KeyboardCallbacksListeners.push_back(callbackListener);
}

void InputManager::UnbindKeyboardCallback(Component* component)
{
	size_t componentIndex = KeyboardCallbacksListeners.size();
	while (componentIndex)
	{
		componentIndex--;

		if (component == KeyboardCallbacksListeners[componentIndex])
			KeyboardCallbacksListeners.erase(KeyboardCallbacksListeners.begin() + componentIndex);
	}
}

KeyActions InputManager::GetKeyState(Keys key)
{
	return KeyBuffer[static_cast<int>(key)];
}

void InputManager::KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	Interactive* engine = static_cast<Interactive*>(glfwGetWindowUserPointer(window));
	InputManager* inputController = engine->InputSystem;

	inputController->KeyBuffer[key] = static_cast<KeyActions>(action);

	if (inputController->KeyboardCallbacksListeners.empty())
		return;

	for (Component* callbackListener : inputController->KeyboardCallbacksListeners)
	{
		callbackListener->KeyboardCallback();
	}
}