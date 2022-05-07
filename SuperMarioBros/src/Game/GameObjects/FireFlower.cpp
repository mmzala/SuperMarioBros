#include "FireFlower.h"
#include "../../Engine/Graphics/Animator.h"
#include "../../Engine/Graphics/Animation.h"

FireFlower::FireFlower(CharacterSettings settings)
	:
	PowerUp::PowerUp(settings)
{
	animator->SetAnimation(Animation(0, 3, 5.0f));
}

FireFlower::~FireFlower()
{}

void FireFlower::Move(const float deltaTime)
{
	velocity.y = std::fmax(velocity.y - gravityAcceleration * deltaTime, -gravity);
	Character::Move(deltaTime);
}
