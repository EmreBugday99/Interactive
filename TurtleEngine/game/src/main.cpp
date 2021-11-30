#include "Engine.h"
#include "TestWorld.h"

int main()
{
	bool successful = false;
	TurtleCore::Engine::Initialize(successful, "Test Shit", 600, 800);
	TurtleCore::Engine::LoadWorld<TestWorld>();

	TurtleCore::Engine::Start();


	return 0;
}
