#include "InputManager.h"
#include "../renderer/Window.h"
#include "../Interactive.h"

namespace IE
{
	InputManager::InputManager()
	{
		glfwSetKeyCallback(Interactive::GameWindow.GetGlfwWindow(), KeyboardCallback);
	}

	void InputManager::KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		Interactive::InputSystem.KeyBuffer[key] = static_cast<KeyActions>(action);
		Interactive::InputSystem.KeysActionsWaitingToBeCleaned[key] = static_cast<KeyActions>(action);
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
}