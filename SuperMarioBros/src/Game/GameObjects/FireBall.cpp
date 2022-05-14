#include "FireBall.h"
#include "Components/Transform.h"
#include "Enemy.h" // Collision checking

FireBall::FireBall(CharacterSettings settings)
	:
	Character::Character(settings),
	rotationSpeed(7.5f),
	travelingDirection(true),
	resetVelocity(false)
{}

FireBall::~FireBall()
{}

void FireBall::Update(const float deltaTime)
{
	if (!IsInFrustum())
	{
		SetInUse(false);
	}

	Character::Update(deltaTime);
	Rotate(deltaTime);
}

void FireBall::SetTravelingDirection(bool right)
{
	travelingDirection = right;
}

void FireBall::SetInUse(bool value)
{
	PoolableObject::SetInUse(value);
	isActive = value;
}

void FireBall::Move(const float deltaTime)
{
	velocity.x = walkingSpeed * (travelingDirection ? 1.0f : -1.0f);

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
		SetInUse(false);
	}

	resetVelocity = true;
}

void FireBall::OnCharacterHit(Character* other)
{
	if (Enemy* enemy = dynamic_cast<Enemy*>(other))
	{
		enemy->isActive = false;
		SetInUse(false);
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
