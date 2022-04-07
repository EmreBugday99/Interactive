#pragma once
#include <cstdint>
#include "KeyCode.h"
#include "KeyState.h"
#include "../TurtleCore.h"

#define KEY_SIZE 256

namespace TurtleCore
{
	class InputManager
	{
	private:
#ifdef TURTLE_OS_WINDOWS
		friend class GlWindowsWindow;
#endif

		KeyState KeyStates[KEY_SIZE] = { {false, false} };

		void ProcessKeyboardInput(uint8_t keycode, bool wasDown, bool isDown);

	public:
		TURTLE_API KeyState GetKeyState(KeyCode keyCode);
	};
}
