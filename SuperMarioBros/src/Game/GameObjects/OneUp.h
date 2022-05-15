#pragma once

#include "Character.h"

class AIMovementComponent;

class OneUp : public Character
{
public:
	OneUp(CharacterSettings settings);
	~OneUp() override;

protected:
	void Move(const float deltaTime) override;
	void CheckCollision(const float deltaTime) override;
	void OnCharacterHit(Character* other) override;

private:
	AIMovementComponent* movementComponent;
};

