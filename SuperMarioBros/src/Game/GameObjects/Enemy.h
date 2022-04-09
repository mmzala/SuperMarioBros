#pragma once

#include "Character.h"

class AIMovementComponent;

enum class EnemyState
{
	Dead = -1,
	Standing = 0,
	Walking = 1,
};

class Enemy : public Character
{
public:
	Enemy(CharacterSettings settings);
	~Enemy() override;

	void Update(const float deltaTime) override;

protected:
	void Move(const float deltaTime) override;
	void CheckCollision(const float deltaTime) override;
	void OnCharacterHit(Character* other) override;
	virtual void UpdateState(EnemyState state);

protected:
	AIMovementComponent* movementComponent;
	EnemyState state;
};

