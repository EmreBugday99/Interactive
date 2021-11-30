#pragma once
#include "../TurtleCore.h"

namespace TurtleCore
{
	TURTLE_API class BaseWindow
	{
	public:
		BaseWindow();
		virtual ~BaseWindow();

		virtual void Initialize(bool& result, const char* windowName, const int& width, const int& height) = 0;
		virtual void ConstructWindow(bool& result) = 0;
		virtual void Update() = 0;
		virtual void Clear() = 0;
		virtual bool IsOpen() = 0;

	protected:
		bool IsRunning;
		int WindowWidth;
		int WindowHeight;
		const char* WindowTitle;

	protected:
		friend class Engine;
		virtual void CloseWindow() = 0;
	};
}