#pragma once

#include "Character.h"
#include "../Settings/CharacterSettings.h"
#include <DirectXMath.h> // XMFLOAT2
#include "../../Engine/Graphics/Animation.h"
#include <vector>

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
	void CheckCollision() override;
	void UpdateState(GoombaState state);

private:
	GoombaState goombaState;
	std::vector<Animation> animations;

	bool walkingRight;
};

