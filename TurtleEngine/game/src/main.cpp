#include "Engine.h"
#include "Worlds/TutorialWorld.h"

int main()
{
	bool successful = false;
	TurtleCore::Engine::Initialize(successful, "Test Shit", 900, 900);
	TurtleCore::Engine::LoadWorld<TutorialWorld>();

	TurtleCore::Engine::Start();

	return 0;
}
