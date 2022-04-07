#pragma once

#include "Character.h"

class AIMovementComponent;

/// <summary>
/// Mushroom used to power up Mario
/// </summary>
class Mushroom : public Character
{
public:
	Mushroom(CharacterSettings settings);
	~Mushroom() override;

	void Update(const float deltaTime) override;

protected:
	void Move(const float deltaTime) override;
	void OnCharacterHit(Character* other) override;

private:
	AIMovementComponent* movementComponent;
};

