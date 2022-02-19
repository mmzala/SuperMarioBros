#include "GameObject.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Physics/RectCollider.h"

GameObject::GameObject(SpriteSettings* spriteSettings)
	:
	transform(new Transform()),
	sprite(new Sprite(SpriteSettings(spriteSettings->textureFile, spriteSettings->spriteSheetSize))),
	collider(new RectCollider(sprite->GetSize(), transform))
{
	sprite->SetFrame(0);
}

GameObject::~GameObject()
{
	delete collider;
	delete sprite;
	delete transform;
}

void GameObject::Update(float deltaTime)
{
	sprite->Draw(transform->GetWorldMatrix());
}
