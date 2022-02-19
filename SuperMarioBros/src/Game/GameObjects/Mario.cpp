#include "Mario.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"

Mario::Mario(SpriteSettings* spriteSettings)
	:
	GameObject::GameObject(spriteSettings)
{
	sprite->SetFrame(24);
}

Mario::~Mario()
{}

void Mario::Update(float deltaTime)
{
	sprite->Draw(transform->GetWorldMatrix());
}
