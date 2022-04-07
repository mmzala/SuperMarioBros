#pragma once

class Character;

class AIMovementComponent
{
public:
	AIMovementComponent(Character* character);
	~AIMovementComponent();

	void Update();
	void ChangeMovingDirection();

private:
	Character* character;
	bool walkingRight;
};

