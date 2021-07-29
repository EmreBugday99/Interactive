#include "InputManager.h"
#include "../includes/CoreIncludes.h"

InputManager::InputManager(Interactive* engine) : Engine(engine)
{
	glfwSetWindowUserPointer(Engine->GameWindow->GetGlfwWindow(), Engine);
	glfwSetKeyCallback(Engine->GameWindow->GetGlfwWindow(), KeyboardCallback);
}

KeyActions InputManager::GetKeyState(Keys key)
{
	return KeyBuffer[static_cast<int>(key)];
}

bool InputManager::IsKeyPressed(Keys key)
{
	return KeyBuffer[static_cast<int>(key)] == KeyActions::PRESS;
}

bool InputManager::IsKeyHold(Keys key)
{
	if (KeyBuffer[static_cast<int>(key)] == KeyActions::PRESS || KeyBuffer[static_cast<int>(key)] == KeyActions::REPEAT)
		return true;

	return false;
}

bool InputManager::IsKeyReleased(Keys key)
{
	return KeyBuffer[static_cast<int>(key)] == KeyActions::RELEASE;
}

void InputManager::ClearKeyStates()
{
	for (auto pair : KeysActionsWaitingToBeCleaned)
	{
		if (pair.second == KeyActions::PRESS || pair.second == KeyActions::RELEASE)
			KeyBuffer[pair.first] = KeyActions::None;
	}
}

void InputManager::KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	Interactive* engine = static_cast<Interactive*>(glfwGetWindowUserPointer(window));
	InputManager* inputController = engine->InputSystem;

	inputController->KeyBuffer[key] = static_cast<KeyActions>(action);
	inputController->KeysActionsWaitingToBeCleaned[key] = static_cast<KeyActions>(action);
}