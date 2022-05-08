#pragma once

#include "Character.h"

class PowerUp : public Character
{
public:
	PowerUp(CharacterSettings settings);
	~PowerUp() override;

protected:
	void CheckCollision(const float deltaTime) override;
};

