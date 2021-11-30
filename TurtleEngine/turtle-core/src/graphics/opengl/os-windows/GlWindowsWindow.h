#pragma once
#ifdef TURTLE_OS_WINDOWS
#include "../../BaseWindow.h"
#include <Windows.h>

namespace TurtleCore
{
	TURTLE_API class GlWindowsWindow : public BaseWindow
	{
	public:
		TURTLE_API GlWindowsWindow();
		TURTLE_API ~GlWindowsWindow();

		TURTLE_API void Initialize(bool& result, const char* windowName, const int& width, const int& height) override;
		TURTLE_API void ConstructWindow(bool& result) override;
		TURTLE_API void Update() override;
		TURTLE_API void Clear() override;
		TURTLE_API bool IsOpen() override { return IsRunning; }

	private:
		HWND WindowHandle;
		ATOM WindowClassId;
		HINSTANCE ModuleInstance;
		HDC DeviceContext;
		HGLRC GlRenderingContext;

	private:
		void InitializeOpenGL(bool& successful);
		static LRESULT WindowsProcessCallback(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

	protected:
		void CloseWindow() override;
	};
}

#endif
