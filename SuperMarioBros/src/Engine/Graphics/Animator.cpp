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
	// Do not update when there is only one frame in animation or animation has no speed
	if (animation.startFrame == animation.endFrame ||
		animation.speed == 0.0f)
	{
		return;
	}

	animationTimer += animation.speed * deltaTime;
	if (animationTimer > 1.0f)
	{
		int currentFrame = sprite->GetFrame();
		sprite->SetFrame(currentFrame + 1);
		if (currentFrame >= animation.endFrame)
		{
			sprite->SetFrame(animation.startFrame);
		}

		animationTimer = 0.0f;
	}
}

void Animator::Update(float deltaTime, float animationSpeed)
{
	// Do not update when there is only one frame in animation or animation has no speed
	if (animation.startFrame == animation.endFrame ||
		animationSpeed == 0.0f)
	{
		return;
	}

	animationTimer += animationSpeed * deltaTime;
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
	if (this->animation == animation) return;

	this->animation = animation;
	sprite->SetFrame(animation.startFrame);
	animationTimer = 0.0f;
}
