#include "Tilemap.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../GameObjects/Components/Transform.h"
#include "../../Engine/SMBEngine.h" // Getting camera
#include "../../Engine/Graphics/Camera.h"
#include <Windows.h> // RECT
#include <algorithm>

Tilemap::Tilemap(std::vector<std::vector<int>> map, TilemapSettings settings)
	:
	map(map),
	sprite(new Sprite(settings.spriteSheetFile, settings.spriteSheetSize)),
	transform(new Transform({ settings.position.x, 0.0f }, 0.0f, settings.scale)),
	tileSize((int)(sprite->GetSize().x * transform->scale.x)) // Size of x and y will be the same anyway :)
{
	transform->position.y = (float)((map.size() - 1) * tileSize) + settings.position.y;
}

Tilemap::~Tilemap()
{
	delete sprite;
	delete transform;
}

void Tilemap::Draw()
{
	DirectX::XMFLOAT2 originalPosition = transform->position;

	DirectX::XMINT2 tilesInFrustum = GetHorizontalTilesInFrustum();

	for (int y = 0; y <= map.size() - 1; y++)
	{
		for (int x = tilesInFrustum.x; x <= tilesInFrustum.y; x++)
		{
			transform->position.x = (float)(x * tileSize);

			if (map[y][x] == 0) continue;
			sprite->SetFrame(map[y][x]);
			sprite->Draw(transform->GetWorldMatrix());
		}

		transform->position.y -= tileSize;
	}

	transform->position = originalPosition;
}

DirectX::XMINT2 Tilemap::GetHorizontalTilesInFrustum()
{
	RECT viewportBounds = SMBEngine::GetInstance()->GetCamera()->GetViewportBounds();
	// Adding tileSize to right coordinate, to prevent player from seeing any artifacts when going fast
	DirectX::XMINT2 mapPosition = GetTilePositionInTilemapCoordinates(
		DirectX::XMFLOAT2((float)viewportBounds.left, (float)viewportBounds.right + tileSize));

	return mapPosition;
}

DirectX::XMINT2 Tilemap::GetTilePositionInTilemapCoordinates(DirectX::XMFLOAT2 worldPosition)
{
	DirectX::XMINT2 mapPosition;
	mapPosition.x = (int)(worldPosition.x / tileSize);
	mapPosition.y = (int)(worldPosition.y / tileSize);

	mapPosition.x = std::clamp((int)mapPosition.x, 0, (int)map[0].size() - 1);
	mapPosition.y = std::clamp((int)mapPosition.y, 0, (int)map[0].size() - 1);

	return mapPosition;
}
