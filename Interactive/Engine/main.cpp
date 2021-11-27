
#include "Engine.h"
#include "TestWorld.h"

int main()
{
	TurtleEngine::Engine::Initialize("Test Game", 400, 800);

	TurtleEngine::Engine::LoadWorld<TestWorld>();

	TurtleEngine::Engine::Start();

	return 0;
}
