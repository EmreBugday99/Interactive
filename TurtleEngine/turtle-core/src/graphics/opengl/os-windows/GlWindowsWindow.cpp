#ifdef TURTLE_OS_WINDOWS
#include "GlWindowsWindow.h"
#include <cassert>
#include "../../../debugging/Logger.h"
#include <glad/glad.h>
#include <glad/glad_wgl.h>

namespace TurtleCore
{
	GlWindowsWindow::GlWindowsWindow()
		: WindowHandle(nullptr), WindowClassId(0),
		ModuleInstance(GetModuleHandle(nullptr)), DeviceContext(nullptr),
		GlRenderingContext(nullptr) {}

	GlWindowsWindow::~GlWindowsWindow()
	{
		DestroyWindow(static_cast<HWND>(WindowHandle));
	}

	void GlWindowsWindow::Initialize(bool& result, const char* windowName, const int& width, const int& height)
	{
		result = false;
		WindowTitle = windowName;

		WNDCLASSEX wc = {};
		ZeroMemory(&wc, sizeof(WNDCLASSEX));
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hInstance = ModuleInstance;
		wc.lpfnWndProc = WindowsProcessCallback;
		wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = L"TurtleCoreClass";
		wc.lpszMenuName = NULL;

		WindowClassId = RegisterClassEx(&wc);
		if (WindowClassId != 0)
			result = true;
		else
			Logger::LogError("Failed to register Windows Class");

		RECT rc = { 0, 0, width, height };
		AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

		WindowWidth = rc.right - rc.left;
		WindowHeight = rc.bottom - rc.top;
	}

	void GlWindowsWindow::ConstructWindow(bool& result)
	{
		result = false;

		WindowHandle = CreateWindowEx(NULL, MAKEINTATOM(WindowClassId), L"TurtleCore",
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
			CW_USEDEFAULT, CW_USEDEFAULT,
			WindowWidth, WindowHeight,
			NULL, NULL, ModuleInstance, NULL);

		if (WindowHandle == nullptr)
		{
			Logger::LogError("Failed to create a Windows window!");
			return;
		}

		SetWindowLongPtr(WindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

		ShowWindow(WindowHandle, SW_SHOW);
		UpdateWindow(WindowHandle);

		bool glInitialized = false;
		InitializeOpenGL(glInitialized);

		if (glInitialized)
		{
			IsRunning = true;
			result = true;

			wchar_t* tempString = new wchar_t[124];
			MultiByteToWideChar(CP_ACP, 0, WindowTitle, -1, tempString, 124);
			SetWindowText(WindowHandle, tempString);
			delete[] tempString;
		}
		else
			Logger::LogError("Failed to initialize OpenGL");
	}

	void GlWindowsWindow::Update()
	{
		SwapBuffers(DeviceContext);

		MSG message = { 0 };
		if (PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				CloseWindow();
			}
			else
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
	}

	void GlWindowsWindow::Clear()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GlWindowsWindow::InitializeOpenGL(bool& successful)
	{
		successful = false;

		DeviceContext = GetDC(WindowHandle);

		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;

		const int format = ChoosePixelFormat(DeviceContext, &pfd);
		if (SetPixelFormat(DeviceContext, format, &pfd) == false)
		{
			Logger::LogError("Failed to set pixel format!");
			return;
		}

		GlRenderingContext = wglCreateContext(DeviceContext);
		if (GlRenderingContext == nullptr)
		{
			Logger::LogError("Failed to create OpenGL Rendering Context!");
			return;
		}

		if (wglMakeCurrent(DeviceContext, GlRenderingContext) == false)
		{
			Logger::LogError("Failed to set current rendering context as OpenGL Rendering Context!");
			return;
		}

		if (gladLoadWGL(DeviceContext) == false)
		{
			Logger::LogError("Failed to load WGL");
			return;
		}

		if (gladLoadGL() == false)
		{
			Logger::LogError("Failed to load Glad");
			return;
		}

		glViewport(0, 0, WindowWidth, WindowHeight);

		Logger::LogNormal(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		Logger::LogNormal(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		Logger::LogNormal(reinterpret_cast<const char*>(glGetString(GL_VERSION)));

		successful = true;
	}

	LRESULT GlWindowsWindow::WindowsProcessCallback(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}

		default:
			return DefWindowProc(windowHandle, message, wParam, lParam);
		}

		return NULL;
	}

	void GlWindowsWindow::CloseWindow()
	{
		IsRunning = false;
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(GlRenderingContext);
		ReleaseDC(WindowHandle, DeviceContext);
	}
}

#endif