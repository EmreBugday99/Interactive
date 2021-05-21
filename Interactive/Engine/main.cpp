#include <iostream>
#include "TestComponent.h"
#include "components/PrimitiveSprite2D.h"
#include "includes/CoreIncludes.h"

int main()
{
	Interactive* engine = new Interactive("Test Game Window");

	Entity* entity1 = engine->ECS->CreateEntity("Test Entity");
	PrimitiveSprite2D* spriteComp = entity1->AddComponent<PrimitiveSprite2D>(
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec2(0.1f, 0.1f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	Entity* entity2 = engine->ECS->CreateEntity("Test Entity2");
	TestComponent* testComponent = entity2->AddComponent<TestComponent>();

	testComponent->Position = glm::vec3(0.5f, 0.8f, 0.0f);
	testComponent->Size = glm::vec2(1.0f, 1.0f);
	testComponent->Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	testComponent->OtherComponent = spriteComp;

	Entity* cameraEntity = engine->ECS->CreateEntity("Camera Entity");
	Camera* cameraComp = cameraEntity->AddComponent<Camera>();
	engine->MainCamera = cameraComp;

	engine->Start();

	delete(engine);

	return 0;
}