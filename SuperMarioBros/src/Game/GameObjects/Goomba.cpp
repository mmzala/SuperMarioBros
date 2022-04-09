#include "Goomba.h"
#include "../../Engine/Graphics/Animator.h" // Setting animations
#include "../Data/Animations.h" // Animation data

Goomba::Goomba(CharacterSettings settings)
	:
	Enemy::Enemy(settings),
	animations(Animations::Goomba::goomba)
{
	UpdateState(EnemyState::Walking);
}

Goomba::~Goomba()
{}

void Goomba::Update(const float deltaTime)
{
	if (IsRightFromCamera()) return;
	Enemy::Update(deltaTime);
}

void Goomba::UpdateState(EnemyState state)
{
	if (this->state == state) return;
	this->state = state;

	switch (state)
	{
	case EnemyState::Walking:
		animator->SetAnimation(animations[Animations::Goomba::AnimationState::Walking]);
		break;
	}
}
