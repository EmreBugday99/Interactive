#pragma once
#include "input/InputManager.h"
#include "renderer/Window.h"
#include "renderer/texture/TextureManager.h"

namespace IE
{
	class Interactive
	{
	public:
		static const char* GameName;
		static Window GameWindow;
		static InputManager InputSystem;
		static TextureManager TextureSystem;

		static void Initialize(const char* gameName);

		void Start();
		void Update();

	private:
		void Close();
	};
}
