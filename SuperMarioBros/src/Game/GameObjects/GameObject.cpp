#include "GameObject.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Physics/RectCollider.h"

GameObject::GameObject(const char* textureFile)
	:
	transform(new Transform()),
	sprite(new Sprite(textureFile, 16)),
	anim(new Animation(0, 255, 60.0f)),
	collider(new RectCollider(sprite->GetSize(), transform)),
	animTimer(0.0f)
{
	sprite->SetFrame(anim->startFrame);
}

GameObject::~GameObject()
{
	delete collider;
	delete anim;
	delete sprite;
	delete transform;
}

void GameObject::Update(float deltaTime)
{
	// Animate
	animTimer += anim->speed * deltaTime;
	if (animTimer > 1.0f)
	{
		sprite->SetFrame(sprite->GetFrame() + 1);
		if (sprite->GetFrame() > anim->endFrame)
		{
			sprite->SetFrame(anim->startFrame);
		}

		animTimer = 0.0f;
	}

	// Draw
	sprite->Draw(transform->GetWorldMatrix());
}
