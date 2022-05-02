#pragma once

#include "Character.h"
#include "../Settings/EnemySettings.h"

class AIMovementComponent;

enum class EnemyState
{
	Dead = -1,
	Walking = 0,
};

class Enemy : public Character
{
public:
	Enemy(EnemySettings settings);
	~Enemy() override;

	void Update(const float deltaTime) override;
	virtual void OnHeadStomp();

protected:
	void Move(const float deltaTime) override;
	void CheckCollision(const float deltaTime) override;
	void OnCharacterHit(Character* other) override;
	virtual void UpdateState(EnemyState state);

private:
	void DeathCountDown(const float deltaTime);

protected:
	AIMovementComponent* movementComponent;
	EnemyState state;

private:
	float timeAfterDeath;
};

