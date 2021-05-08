#include <iostream>
#include "InteractiveEngine.h"
#include "components/PrimitiveSprite2D.h"
#include "components/Camera.h"
#include "ecs/Entity.h"
#include "ecs/EntityManager.h"

int main()
{
	std::cout << "Hello World!" << std::endl;

	InteractiveEngine* engine = new InteractiveEngine();
	engine->Initialize();
	
	Entity* entity1 = engine->ECS->CreateEntity("Test Entity");
	PrimitiveSprite2D* spriteComp = entity1->AddComponent<PrimitiveSprite2D>(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec2(0.1f, 0.1f),
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	Entity* cameraEntity = engine->ECS->CreateEntity("Camera Entity");
	Camera* cameraComp = cameraEntity->AddComponent<Camera>();
	engine->MainCamera = cameraComp;
	
	engine->Start();

	delete(engine);

	return 0;
}
