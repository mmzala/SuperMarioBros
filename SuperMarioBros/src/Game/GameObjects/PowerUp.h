#pragma once

#include "Character.h"

class PowerUp : public Character
{
public:
	PowerUp(CharacterSettings settings);
	~PowerUp() override;
};

