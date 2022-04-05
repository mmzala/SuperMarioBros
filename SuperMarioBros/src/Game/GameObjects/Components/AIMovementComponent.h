#pragma once

class Character;

class AIMovementComponent
{
public:
	AIMovementComponent(Character* character);
	~AIMovementComponent();

	void Update();

private:
	Character* character;
	bool walkingRight;
};

