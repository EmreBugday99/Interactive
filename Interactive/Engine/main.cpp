#include <iostream>
#include "TestComponent.h"
#include "TestComponent2.h"
#include "components/PrimitiveSprite2D.h"
#include "includes/CoreIncludes.h"

int main()
{
	Interactive* engine = new Interactive("Test Game Window");

	Entity* entity1 = engine->ECManager->CreateEntity("Test Entity");
	PrimitiveSprite2D* spriteComp = entity1->AddComponent<PrimitiveSprite2D>(
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec2(50.0f, 50.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	Entity* entity2 = engine->ECManager->CreateEntity("Test Entity2");
	TestComponent* testComponent = entity2->AddComponent<TestComponent>();

	testComponent->Position = glm::vec3(0.5f, 0.8f, 0.0f);
	testComponent->Size = glm::vec2(100.0f, 100.0f);
	testComponent->Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	Entity* cameraEntity = engine->ECManager->CreateEntity("Camera Entity");
	Camera* cameraComp = cameraEntity->AddComponent<Camera>();
	engine->MainCamera = cameraComp;

	Entity* smileyEntity = engine->ECManager->CreateEntity("Smiley Entity");
	TestComponent2* testComp2 = smileyEntity->AddComponent<TestComponent2>();
	testComp2->Position = glm::vec3(0.5f, 0.1f, 0.0f);
	testComp2->Size = glm::vec2(100.0f, 100.0f);
	testComp2->Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	engine->Start();

	delete(engine);

	return 0;
}