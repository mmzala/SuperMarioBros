#pragma once

#include "PowerUp.h"

class AIMovementComponent;

/// <summary>
/// Mushroom used to power up Mario
/// </summary>
class Mushroom : public PowerUp
{
public:
	Mushroom(CharacterSettings settings);
	~Mushroom() override;

protected:
	void Move(const float deltaTime) override;
	void OnCharacterHit(Character* other) override;

private:
	AIMovementComponent* movementComponent;
};

