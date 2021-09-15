#include "components/EcsTestComponent.h"
#include "ecs/ECSManager.hpp"
#include "ecs/Entity.hpp"

int main()
{
	using namespace Interactive;
	Interactive::Entity* entity = ECSManager::CreateEntity();

	ECSManager::CreateComponent<EcsTestComponent>(entity);
	EcsTestComponent* testComponent = ECSManager::FetchComponent<EcsTestComponent>(entity);

	testComponent->SayHello();

	testComponent->TestInteger = 100;
	std::cout << testComponent->TestInteger << std::endl;

	return 0;
}