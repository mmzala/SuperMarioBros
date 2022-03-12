#include "Animator.h"
#include "Sprite.h"

Animator::Animator(Sprite* sprite)
	:
	sprite(sprite),
	animation(0, 0, 0),
	animationTimer(0.0f)
{}

Animator::~Animator()
{}

void Animator::Update(float deltaTime)
{
	animationTimer += animation.speed * deltaTime;
	if (animationTimer > 1.0f)
	{
		sprite->SetFrame(sprite->GetFrame() + 1);
		if (sprite->GetFrame() > animation.endFrame)
		{
			sprite->SetFrame(animation.startFrame);
		}

		animationTimer = 0.0f;
	}
}

void Animator::SetAnimation(Animation animation)
{
	this->animation = animation;
	sprite->SetFrame(animation.startFrame);
	animationTimer = 0.0f;
}
