#include "InputManager.h"
#include "../debugging/Logger.h"

void TurtleCore::InputManager::ProcessKeyboardInput(uint8_t keycode, bool wasDown, bool isDown)
{
	KeyStates[keycode].isDown = isDown;
	KeyStates[keycode].wasDown = wasDown;
}

TurtleCore::KeyState TurtleCore::InputManager::GetKeyState(KeyCode keyCode)
{
	if (static_cast<uint8_t>(keyCode) > KEY_SIZE)
	{
		Logger::LogError("Key Code bigger than key size!");
		return {};
	}

	return KeyStates[static_cast<uint8_t>(keyCode)];
}
