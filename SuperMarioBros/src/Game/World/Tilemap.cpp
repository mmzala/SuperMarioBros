#include "Tilemap.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../GameObjects/Components/Transform.h"
#include "../../Engine/SMBEngine.h" // Getting camera
#include "../../Engine/Graphics/Camera.h"
#include <algorithm> // std::clamp

Tilemap::Tilemap(TilemapSettings settings)
	:
	tilemap(settings.tilemap),
	collisionMap(settings.collisionMap),
	sprite(new Sprite(SpriteSettings(settings.spriteSheetFile, settings.spriteSheetSize))),
	transform(new Transform(settings.position, 0.0f, settings.scale)),
	tileSizeScaled((int)(sprite->GetSize().x * transform->scale.x)) // Size of x and y will be the same anyway :)
{}

Tilemap::~Tilemap()
{
	delete sprite;
	delete transform;
}

void Tilemap::Draw()
{
	DirectX::XMFLOAT2 originalPosition = transform->position;
	DirectX::XMINT2 tilesInFrustum = GetHorizontalTilesInFrustum();

	for (int y = tilemap.size() - 1; y > 0; y--)
	{
		for (int x = tilesInFrustum.x; x <= tilesInFrustum.y; x++)
		{
			transform->position.x = (float)(x * tileSizeScaled + originalPosition.x);

			if (tilemap[y][x] == 0) continue;
			sprite->SetFrame(tilemap[y][x]);
			sprite->Draw(transform->GetWorldMatrix());
		}

		transform->position.y += tileSizeScaled;
	}

	transform->position = originalPosition;
}

DirectX::XMFLOAT2 Tilemap::GetPositionInTilemapCoordinates(DirectX::XMFLOAT2 worldPosition)
{
	float halfTileSize = (float)(tileSizeScaled / 2);
	float topTilePosition = (tilemap.size() - static_cast<unsigned long long>(1)) * tileSizeScaled + transform->position.y;

	DirectX::XMFLOAT2 mapPosition = DirectX::XMFLOAT2();
	mapPosition.x = (transform->position.x + worldPosition.x) / tileSizeScaled;
	mapPosition.y = (topTilePosition - worldPosition.y + halfTileSize) / tileSizeScaled;

	return mapPosition;
}

RECT Tilemap::GetTileBounds(DirectX::XMINT2 tilemapPosition)
{
	RECT bounds = RECT();
	float halfTileSize = (float)(tileSizeScaled / 2);
	float topTilePosition = (tilemap.size() - static_cast<unsigned long long>(1)) * tileSizeScaled + transform->position.y;

	// Calculate world position somehow
	bounds.left = (LONG)((tilemapPosition.x * tileSizeScaled + transform->position.x) + halfTileSize);
	bounds.right = (LONG)(tileSizeScaled);
	bounds.bottom = (LONG)(topTilePosition - (tilemapPosition.y * tileSizeScaled) - halfTileSize);
	bounds.top = (LONG)(tileSizeScaled);

	return bounds;
}

bool Tilemap::CheckCollisionTile(DirectX::XMINT2 tilemapPosition)
{
	// Return true when tilemapPosition does not exist
	if ((tilemapPosition.y > collisionMap.size() - 1) || 
		tilemapPosition.y < 0 ||
		(tilemapPosition.x > collisionMap[0].size() - 1) || 
		tilemapPosition.x < 0)
	{
		return true;
	}

	return collisionMap[tilemapPosition.y][tilemapPosition.x];
}

DirectX::XMINT2 Tilemap::GetHorizontalTilesInFrustum()
{
	RECT viewportBounds = SMBEngine::GetInstance()->GetCamera()->GetViewportBounds();

	// Adding tileSizeScaled to right coordinate, to prevent player from seeing any artifacts when going fast
	DirectX::XMFLOAT2 worldPosition = DirectX::XMFLOAT2((float)viewportBounds.left,
		(float)viewportBounds.right + tileSizeScaled);

	// Both x and y are horizontal coordinates in this case
	DirectX::XMINT2 mapPosition = DirectX::XMINT2();
	mapPosition.x = (int)(transform->position.x + worldPosition.x) / tileSizeScaled;
	mapPosition.y = (int)(transform->position.x + worldPosition.y) / tileSizeScaled;

	mapPosition.x = std::clamp(mapPosition.x, 0, (int)tilemap[0].size() - 1);
	mapPosition.y = std::clamp(mapPosition.y, 0, (int)tilemap[0].size() - 1);

	return mapPosition;
}
