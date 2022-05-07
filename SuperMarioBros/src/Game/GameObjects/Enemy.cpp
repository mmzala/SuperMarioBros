#include "Enemy.h"
#include "Components/Transform.h" // Geting world matrix for sprite drawing
#include "../../Engine/Graphics/Sprite.h" // Drawing sprite
#include "../../Engine/Graphics/Animator.h" // Animating sprite
#include "Components/AIMovementComponent.h" // Movement

Enemy::Enemy(EnemySettings settings)
	:
	Character::Character(settings),
	movementComponent(new AIMovementComponent(this)),
	state(EnemyState::Dead), // Temporary at the beginning
	timeAfterDeath(settings.timeAfterDeath)
{}

Enemy::~Enemy()
{
	delete movementComponent;
}

void Enemy::Update(const float deltaTime)
{
	switch (state)
	{
	case EnemyState::Dead:
		DeathCountDown(deltaTime);
		break;

	case EnemyState::Walking:
		Move(deltaTime);
		break;
	}

	animator->Update(deltaTime);
	sprite->Draw(transform->GetWorldMatrix());
}

void Enemy::OnHeadStomp()
{}

void Enemy::Move(const float deltaTime)
{
	movementComponent->Update(deltaTime);
	Character::Move(deltaTime);
}

void Enemy::CheckCollision(const float deltaTime)
{
	Character::CheckCollision(deltaTime);
}

void Enemy::OnCharacterHit(Character* other)
{
	movementComponent->ChangeMovingDirection();
}

void Enemy::UpdateState(EnemyState state)
{}

void Enemy::DeathCountDown(const float deltaTime)
{
	timeAfterDeath -= deltaTime;
	if (timeAfterDeath <= 0.0f)
	{
		isActive = false;
	}
}
