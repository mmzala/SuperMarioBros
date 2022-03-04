#pragma once

#include "GameObject.h"
#include <DirectXMath.h> // XMFLOAT2
#include <Windows.h> // RECT

class Tilemap;

class Mario : public GameObject
{
public:
	Mario(SpriteSettings* spriteSettings, Tilemap* tilemap);
	~Mario() override;

	void Update(const float deltaTime) override;

private:
	void Move(DirectX::XMFLOAT2& velocity, const float deltaTime);
	void CheckCollision(DirectX::XMFLOAT2& velocity);
	void CheckBottomTilesCollision(RECT bounds, DirectX::XMFLOAT2 fTilemapPosition, DirectX::XMFLOAT2& velocity);

private:
	Tilemap* tilemap;
};

