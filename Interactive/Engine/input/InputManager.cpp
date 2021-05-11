#include "InputManager.h"
#include "../InteractiveEngine.h"
#include "../ecs/Component.h"
#include "../renderer/Window.h"

InputManager::InputManager(InteractiveEngine* engine) : Engine(engine)
{
	glfwSetWindowUserPointer(Engine->GameWindow->GetGlfwWindow(), Engine);
	glfwSetKeyCallback(Engine->GameWindow->GetGlfwWindow(), KeyboardCallback);
}

void InputManager::BindKeyboardCallback(Component* callbackListener)
{
	KeyboardCallbacksListeners.push_back(callbackListener);
}

KeyActions InputManager::GetKeyState(Keys key)
{
	return KeyBuffer[static_cast<int>(key)];
}

void InputManager::KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	InteractiveEngine* engine = static_cast<InteractiveEngine*>(glfwGetWindowUserPointer(window));
	InputManager* inputController = engine->InputSystem;
	inputController->KeyBuffer[key] = static_cast<KeyActions>(action);

	if (inputController->KeyboardCallbacksListeners.empty())
		return;

	for (Component* callbackListener : inputController->KeyboardCallbacksListeners)
	{
		callbackListener->KeyboardCallback();
	}
}