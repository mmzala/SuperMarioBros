#include "Enemy.h"
#include "Components/Transform.h" // Geting world matrix for sprite drawing
#include "../../Engine/Graphics/Sprite.h" // Drawing sprite
#include "../../Engine/Graphics/Animator.h" // Animating sprite
#include "Components/AIMovementComponent.h" // Movement

Enemy::Enemy(CharacterSettings settings)
	:
	Character::Character(settings),
	movementComponent(new AIMovementComponent(this)),
	state(EnemyState::Standing)
{}

Enemy::~Enemy()
{
	delete movementComponent;
}

void Enemy::Update(const float deltaTime)
{
	if (state == EnemyState::Walking) Move(deltaTime);
	animator->Update(deltaTime);
	sprite->Draw(transform->GetWorldMatrix());
}

void Enemy::Move(const float deltaTime)
{
	movementComponent->Update();
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
