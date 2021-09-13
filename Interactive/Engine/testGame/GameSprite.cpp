#include "GameSprite.h"
#include "../components/Transform.h"

void GameSprite::Initialize()
{
	Sprite2D::Initialize();

	Texture* smileyTexture = GetEnginePtr()->TextureSystem->CreateTexture("smiley", "smiley.jpg");
	AttachTexture(smileyTexture);

	GetTransform()->SetSize(glm::vec2(50.0f, 50.0f));

}

void GameSprite::BeginPlay()
{
	Sprite2D::BeginPlay();

}
