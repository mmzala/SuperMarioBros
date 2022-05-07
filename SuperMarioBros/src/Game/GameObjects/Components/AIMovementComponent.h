#pragma once

class Character;

class AIMovementComponent
{
public:
	AIMovementComponent(Character* character);
	~AIMovementComponent();

	void Update(const float deltaTime);
	void ChangeMovingDirection();

private:
	Character* character;
	bool walkingRight;
};

