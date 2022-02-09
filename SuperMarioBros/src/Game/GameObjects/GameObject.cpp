#include "GameObject.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Physics/RectCollider.h"

GameObject::GameObject(const char* textureFile)
	:
	transform(new Transform()),
	sprite(new Sprite(textureFile)),
	collider(new RectCollider(sprite->GetSize(), transform))
{}

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
