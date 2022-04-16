#include "Engine.h"
#include "TestWorld.h"

int main()
{
	bool successful = false;
	TurtleCore::Engine::Initialize(successful, "Test Shit", 900, 900);
	TurtleCore::Engine::LoadWorld<TestWorld>();

	TurtleCore::Engine::Start();


	return 0;
}
