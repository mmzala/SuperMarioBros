#include "Goomba.h"
#include "../../Engine/Graphics/Animator.h" // Setting animations
#include "../Data/Animations.h" // Animation data

// Ignoring collision
#include "../../Engine/Physics/CharacterCollider.h"
#include "Mushroom.h"

Goomba::Goomba(CharacterSettings settings)
	:
	Enemy::Enemy(settings),
	animations(Animations::Goomba::goomba)
{
	UpdateState(EnemyState::Walking);
	characterCollider->AddCharacterTypeToIgnore<Mushroom>();
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
