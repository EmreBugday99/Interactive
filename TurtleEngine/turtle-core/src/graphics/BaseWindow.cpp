#include "BaseWindow.h"

namespace TurtleCore
{
	BaseWindow::BaseWindow()
		: IsRunning(false), WindowWidth(0), WindowHeight(0), WindowTitle(nullptr) {}

	BaseWindow::~BaseWindow()
	{
	}

}