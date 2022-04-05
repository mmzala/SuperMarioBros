#pragma once

#include "Character.h"
#include "../Settings/CharacterSettings.h"
#include <DirectXMath.h> // XMFLOAT2
#include "../../Engine/Graphics/Animation.h"
#include <vector>

class AIMovementComponent;

enum class GoombaState
{
	None = 0, // None is used only at the start
	Walking = 1,
	Dead = 2,
};

class Goomba : public Character
{
public:
	Goomba(CharacterSettings settings);
	~Goomba() override;

	void Update(const float deltaTime) override;

protected:
	void Move(const float deltaTime) override;
	void CheckCollision(const float deltaTime) override;
	void UpdateState(GoombaState state);

private:
	AIMovementComponent* movementComponent;
	GoombaState goombaState;
	std::vector<Animation> animations;
};

