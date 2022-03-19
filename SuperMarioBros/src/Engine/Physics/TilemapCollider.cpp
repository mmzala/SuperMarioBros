#include "TilemapCollider.h"
#include "RectCollider.h"
#include "../../Game/World/Tilemap.h"
#include "../../Utils/Math.h" // Lerp
// lerp is only included in C++20, but then I would need to rewrite my world collision vector initialization, so no thanks :)
#include <cmath> // floor / ceil

TilemapCollider::TilemapCollider(RectCollider* rectCollider, Tilemap* tilemap)
	:
	rectCollider(rectCollider),
	tilemap(tilemap),
	collisions()
{}

TilemapCollider::~TilemapCollider()
{}

void TilemapCollider::Update(DirectX::XMFLOAT2& velocity, const float deltaTime)
{
	Rect bounds = rectCollider->GetBounds();
	// Sometimes Mario would get stuck after jumping, but subtracting 0.01f fixed it :)
	DirectX::XMFLOAT2 deltaVelocity = DirectX::XMFLOAT2(velocity.x * deltaTime, velocity.y * deltaTime - 0.01f);
	Rect vBounds = rectCollider->GetBoundsWithOffset(deltaVelocity);

	bool collidedBottom = CheckSideCollision(bounds, vBounds, bounds.x, bounds.x + bounds.width, vBounds.y, CheckSide::Bottom);
	bool collidedTop = CheckSideCollision(bounds, vBounds, bounds.x, bounds.x + bounds.width, vBounds.y + vBounds.height, CheckSide::Top);
	if (collidedBottom || collidedTop)
	{
		velocity.y = 0.0f;
	}

	bool collidedLeft = CheckSideCollision(bounds, vBounds, bounds.y, bounds.y + bounds.height, vBounds.x, CheckSide::Left);
	bool collidedRight = CheckSideCollision(bounds, vBounds, bounds.y, bounds.y + bounds.height, vBounds.x + vBounds.width, CheckSide::Right);
	if (collidedLeft || collidedRight)
	{
		velocity.x = 0.0f;
	}

	CheckSide sidesDetected{};
	if (collidedBottom) sidesDetected |= CheckSide::Bottom;
	if (collidedTop) sidesDetected |= CheckSide::Top;
	if (collidedLeft) sidesDetected |= CheckSide::Left;
	if (collidedRight) sidesDetected |= CheckSide::Right;
	collisions = sidesDetected;
}

CheckSide TilemapCollider::DetectedCollisions()
{
	return collisions;
}

bool TilemapCollider::CheckSideCollision(Rect bounds, Rect vBounds, float fromPosition, float toPosition, float sidePosition, CheckSide side)
{
	float tileSize = tilemap->GetTileSize();
	int iterations = static_cast<int>((toPosition - fromPosition) / tileSize); // Calculate how many checks it takes to check for all tiles that can be in proximity
	iterations += 2; // We always want to check atleast the corners

	for (int i = 0; i < iterations; i++)
	{
		float checkProgress = static_cast<float>(i) / (iterations - 1);
		float positionProgress = Math::Lerp(fromPosition, toPosition, checkProgress);
		DirectX::XMFLOAT2 checkPosition = GetCheckPosition(positionProgress, sidePosition, side);
		DirectX::XMFLOAT2 tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);

		if (CheckTileCollision(vBounds, tilemapPosition, side))
		{
			return true;
		}
	}

	return false;
}

bool TilemapCollider::CheckTileCollision(Rect bounds, DirectX::XMFLOAT2 fTilemapPosition, CheckSide side)
{
	DirectX::XMINT2 tilemapPosition = DirectX::XMINT2((int32_t)std::round(fTilemapPosition.x), (int32_t)std::round(fTilemapPosition.y));
	if (!tilemap->CheckCollisionTile(tilemapPosition)) return false;
	return Collision::TilemapCheck(tilemap->GetTileBounds(tilemapPosition), bounds, side);
}

DirectX::XMFLOAT2 TilemapCollider::GetCheckPosition(float positionProgress, float sidePosition, CheckSide side)
{
	switch (side)
	{
	case CheckSide::Top:
	case CheckSide::Bottom:
		return DirectX::XMFLOAT2(positionProgress, sidePosition);
		break;
	case CheckSide::Right:
	case CheckSide::Left:
		return DirectX::XMFLOAT2(sidePosition, positionProgress);
		break;
	}

	return DirectX::XMFLOAT2();
}
