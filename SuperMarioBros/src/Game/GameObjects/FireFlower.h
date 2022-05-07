#pragma once

#include "PowerUp.h"

/// <summary>
/// Fire flower used to power up Mario
/// </summary>
class FireFlower : public PowerUp
{
public:
	FireFlower(CharacterSettings settings);
	~FireFlower() override;

protected:
	void Move(const float deltaTime) override;
};

