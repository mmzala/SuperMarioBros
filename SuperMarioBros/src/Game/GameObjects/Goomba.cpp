#include "Goomba.h"
#include "../../Engine/Graphics/Animator.h" // Setting animations
#include "../Data/Animations.h" // Animation data

// Ignoring collision
#include "../../Engine/Physics/CharacterCollider.h"
#include "Mushroom.h"
#include "FireFlower.h"
#include "Mario.h"

Goomba::Goomba(EnemySettings settings)
	:
	Enemy::Enemy(settings),
	animations(Animations::Goomba::goomba)
{
	UpdateState(EnemyState::Walking);
	characterCollider->AddCharacterTypeToIgnore<Mushroom>();
	characterCollider->AddCharacterTypeToIgnore<Mario>();
	characterCollider->AddCharacterTypeToIgnore<FireFlower>();
}

Goomba::~Goomba()
{}

void Goomba::Update(const float deltaTime)
{
	if (!WasSeen()) return;
	Enemy::Update(deltaTime);
}

void Goomba::OnHeadStomp()
{
	characterCollider->ignoreCollision = true;
	UpdateState(EnemyState::Dead);
}

void Goomba::UpdateState(EnemyState state)
{
	if (this->state == state) return;
	this->state = state;

	switch (state)
	{
	case EnemyState::Dead:
		animator->SetAnimation(animations[Animations::Goomba::AnimationState::Dead]);
		break;

	case EnemyState::Walking:
		animator->SetAnimation(animations[Animations::Goomba::AnimationState::Walking]);
		break;
	}
}
