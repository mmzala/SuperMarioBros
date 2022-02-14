#include "Tilemap.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../GameObjects/Components/Transform.h"

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

	for (int y = 0; y <= map.size() - 1; y++)
	{
		for (int x = 0; x <= map[y].size() - 1; x++)
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
