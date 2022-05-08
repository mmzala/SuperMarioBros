#include "PowerUp.h"

PowerUp::PowerUp(CharacterSettings settings)
	:
	Character::Character(settings)
{}

PowerUp::~PowerUp()
{}

void PowerUp::CheckCollision(const float deltaTime)
{
	Character::CheckCollision(deltaTime);
	CheckFalledOffMap(true);
}
