#pragma once

#include "GameObject.h"
#include <DirectXMath.h> // XMFLOAT2
#include "../../Engine/Graphics/Animation.h"
#include <vector>

class Animator;
class Tilemap;
class TilemapCollider;

enum class GoombaState
{
	None = 0, // None is used only at the start
	Walking = 1,
	Dead = 2,
};

class Goomba : public GameObject
{
public:
	Goomba(SpriteSettings* spriteSettings, Tilemap* tilemap);
	~Goomba() override;

	void Update(const float deltaTime) override;

private:
	void Move(DirectX::XMFLOAT2& velocity, const float deltaTime);
	void UpdateState(GoombaState state);

private:
	Animator* animator;
	Tilemap* tilemap;
	TilemapCollider* tilemapCollider;

	GoombaState goombaState;
	std::vector<Animation> animations;

	bool walkingRight;
};

