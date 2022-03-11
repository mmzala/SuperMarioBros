#include "TilemapCollider.h"
#include "RectCollider.h"
#include "../../Game/World/Tilemap.h"
#include <cmath> // floor and ceil

TilemapCollider::TilemapCollider(RectCollider* rectCollider, Tilemap* tilemap)
	:
	rectCollider(rectCollider),
	tilemap(tilemap)
{}

TilemapCollider::~TilemapCollider()
{}

void TilemapCollider::Update(DirectX::XMFLOAT2& velocity)
{
	Rect bounds = rectCollider->GetBounds();
	Rect vBounds = rectCollider->GetBoundsWithOffset(velocity);

	// Bottom left collision
	DirectX::XMFLOAT2 checkPosition = DirectX::XMFLOAT2(bounds.x, vBounds.y);
	DirectX::XMFLOAT2 tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Bottom))
	{
		velocity.y = 0.0f;
	}

	// Bottom right collision
	checkPosition = DirectX::XMFLOAT2(bounds.x + bounds.width, vBounds.y);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Bottom))
	{
		velocity.y = 0.0f;
	}

	// Top left collision
	checkPosition = DirectX::XMFLOAT2(bounds.x, vBounds.y + vBounds.height);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Top))
	{
		velocity.y = 0.0f;
	}

	// Top right collision
	checkPosition = DirectX::XMFLOAT2(bounds.x + bounds.width, vBounds.y + vBounds.height);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Top))
	{
		velocity.y = 0.0f;
	}

	// Left bottom collision
	checkPosition = DirectX::XMFLOAT2(vBounds.x, bounds.y);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Left))
	{
		velocity.x = 0.0f;
	}

	// Left top collision
	checkPosition = DirectX::XMFLOAT2(vBounds.x, bounds.y + bounds.height);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Left))
	{
		velocity.x = 0.0f;
	}

	// Right bottom collision
	checkPosition = DirectX::XMFLOAT2(vBounds.x + vBounds.width, bounds.y);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Right))
	{
		velocity.x = 0.0f;
	}

	// Right top collision
	checkPosition = DirectX::XMFLOAT2(vBounds.x + vBounds.width, bounds.y + bounds.height);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Right))
	{
		velocity.x = 0.0f;
	}
}

bool TilemapCollider::CheckTileCollision(Rect bounds, DirectX::XMFLOAT2 fTilemapPosition, CheckSide side)
{
	DirectX::XMINT2 tilemapPosition = DirectX::XMINT2((int32_t)std::round(fTilemapPosition.x), (int32_t)std::round(fTilemapPosition.y));
	if (!tilemap->CheckCollisionTile(tilemapPosition)) return false;
	return Collision::TilemapCheck(tilemap->GetTileBounds(tilemapPosition), bounds, side);
}
