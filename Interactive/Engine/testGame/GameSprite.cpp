#include "GameSprite.h"
#include "../components/Transform.h"
#include "../reflection-system/ReflectionSystem.hpp"

void GameSprite::Initialize()
{
	Sprite2D::Initialize();

	ReflectionSystem::AddInheritedClass<GameSprite>(Reflection, "GameSprite");
	ReflectionSystem::UpdateClassReflection<GameSprite>(Reflection, "GameSprite");

	Texture* smileyTexture = GetEnginePtr()->TextureSystem->CreateTexture("smiley", "smiley.jpg");
	AttachTexture(smileyTexture);

	GetTransform()->SetSize(glm::vec2(500.0f, 500.0f));

}

void GameSprite::BeginPlay()
{
	Sprite2D::BeginPlay();


	for (ClassReflection reflection : Reflection.InheritanceTree)
	{

		std::cout << "Inheritance Tree: " << reflection.GetTypeName() << std::endl;
	}

	std::cout << "Size: " << Reflection.SizeInBytes << std::endl;
}
