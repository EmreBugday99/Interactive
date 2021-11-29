#include <iostream>
#include "TurtleCore.h"
#include "debugging/Logger.h"

namespace TurtleCore
{
	TURTLE_API void SayShit();
}

int main()
{
	std::cout << "Hello" << std::endl;
	TurtleCore::SayShit();
	TurtleEngine::Logger::LogError("It kind a works?");

	return 0;
}