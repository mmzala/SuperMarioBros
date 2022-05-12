#include "FireBall.h"
#include "Components/Transform.h"
#include "Enemy.h" // Collision checking

FireBall::FireBall(CharacterSettings settings)
	:
	Character::Character(settings),
	rotationSpeed(5.0f),
	resetVelocity(false)
{}

FireBall::~FireBall()
{}

void FireBall::Update(const float deltaTime)
{
	Character::Update(deltaTime);
	Rotate(deltaTime);
}

void FireBall::Move(const float deltaTime)
{
	velocity.x = walkingSpeed;

	if (resetVelocity)
	{
		velocity.y = gravity;
		resetVelocity = false;
	}
	else
	{
		velocity.y = std::fmax(velocity.y - gravityAcceleration * deltaTime, -gravity);
	}

	Character::Move(deltaTime);
}

void FireBall::OnTileHit(CheckSide side, int tileType, DirectX::XMINT2 tilemapPosition, DirectX::XMFLOAT2 worldPosition)
{
	// If we hit any other side, the fireball dissapears
	if (side != CheckSide::Bottom)
	{
		isActive = false;
	}

	resetVelocity = true;
}

void FireBall::OnCharacterHit(Character* other)
{
	if (Enemy* enemy = dynamic_cast<Enemy*>(other))
	{
		enemy->isActive = false;
		isActive = false;
	}
}

void FireBall::Rotate(const float deltaTime)
{
	transform->rotation -= rotationSpeed * deltaTime;
	if (transform->rotation > 360.0f)
	{
		transform->rotation = 0.0f;
	}
}
