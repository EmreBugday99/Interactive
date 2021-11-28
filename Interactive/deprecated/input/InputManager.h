#pragma once
#include <map>
#include "KeyActions.h"
#include <GLFW/glfw3.h>


namespace IE
{
	enum class Keys;
	class InputManager
	{
	public:

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

		InputManager();

		static void KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
	};
}
