#include <iostream>
#include "reflection/RuntimeReflection.hpp"
#include "reflection/TestShit.hpp"
#include "reflection/TestStruct.h"

int main()
{
	using namespace  Interactive;

	RuntimeReflection::Initialize();

	TestShit* testStructyy = new TestShit();

	TestStruct* testStruct = new TestStruct();

	ClassDefinition* def = RuntimeReflection::FetchClassDefinition(testStruct->DefinitionId);
	ClassDefinition* def2 = RuntimeReflection::FetchClassDefinition(testStructyy->DefinitionId);

	std::cout << "Def Id: " << def->DefinitionId << std::endl;
	std::cout << "Def Name: " << def->DefinitionName << std::endl;
	std::cout << "Def Size: " << def->DefinitionSize << std::endl;

	std::cout << "Runtime Class Def: " << testStruct->RuntimeReflection->Definition->DefinitionName << std::endl;

	std::cout << "Def2 Id: " << def2->DefinitionId << std::endl;
	std::cout << "Def2 Name: " << def2->DefinitionName << std::endl;
	std::cout << "Def2 Size: " << def2->DefinitionSize << std::endl;

	std::cout << "Runtime Class Def2: " << testStructyy->RuntimeReflection->Definition->DefinitionName << std::endl;

	delete testStruct;

	//std::string className = RuntimeReflection::GET_CLASS_NAME;

	//std::cout << className << std::endl;

	return 0;

	//ECSMemory<Entity2>::InitializeMemory();
	//ECSMemory<Entity2>::SetAlias("Entity");

	//ECSMemory<TestComponent>::InitializeMemory();
	//ECSMemory<TestComponent>::SetAlias("TestComponent");

	//ECSMemory<TestComponent2>::InitializeMemory();
	//ECSMemory<TestComponent2>::SetAlias("TestComponent2");

	//ECSMemory<TestComponent3>::InitializeMemory();
	//ECSMemory<TestComponent3>::SetAlias("TestComponent3");

	//const auto ecsReturnEntity = ECSManager::CreateEntity();
	//const auto ecsReturnEntity2 = ECSManager::CreateEntity();

	//ECSManager::CreateComponent<TestComponent>(ecsReturnEntity.ReturnIndex);
	//ECSManager::CreateComponent<TestComponent2>(ecsReturnEntity.ReturnIndex);
	//ECSManager::CreateComponent<TestComponent>(ecsReturnEntity2.ReturnIndex);
	//ECSManager::CreateComponent<TestComponent2>(ecsReturnEntity2.ReturnIndex);

	//ECSMemory<TestComponent3>::Add();
	//ECSMemory<TestComponent3>::Add();

	//TestSystem* testSystem = new TestSystem();
	//TestSystem2* testSystem2 = new TestSystem2();

	//ECSManager::AddSystem(testSystem);
	//ECSManager::AddSystem(testSystem2);

	//while (true)
	//{
	//	ECSManager::Update();
	//}

	return 0;
}