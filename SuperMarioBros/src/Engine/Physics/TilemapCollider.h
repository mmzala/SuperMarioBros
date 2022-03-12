#pragma once

#include <DirectXMath.h> // XMFLOAT2
#include "../../Utils/Rect.h"
#include "../../Engine/Physics/Collision.h" // Collision check and CheckSide enum

class RectCollider;
class Tilemap;

class TilemapCollider
{
public:
	TilemapCollider(RectCollider* rectCollider, Tilemap* tilemap);
	~TilemapCollider();

	void Update(DirectX::XMFLOAT2& velocity);

private:
	bool CheckSideCollision(Rect bounds, Rect vBounds, float fromPosition, float toPosition, float sidePosition, CheckSide side);
	bool CheckTileCollision(Rect bounds, DirectX::XMFLOAT2 fTilemapPosition, CheckSide side);
	DirectX::XMFLOAT2 GetCheckPosition(float positionProgress, float sidePosition, CheckSide side);

private:
	RectCollider* rectCollider;
	Tilemap* tilemap;
};

