#include "World1L1.h"
#include "../Data/Worlds.h"
#include "Tilemap.h"

World1L1::World1L1()
{
	// Tilemap setup
	questionMarkBlock = new TilemapAnimation(6, 8, 0.8f);
	std::vector<TilemapAnimation*> tilemapAnimations = { questionMarkBlock };
	TilemapSettings tilemapSettings;
	tilemapSettings.tilemap = Worlds::world1d1;
	tilemapSettings.collisionMap = Worlds::Collision::world1d1;
	tilemapSettings.spriteSheetFile = "assets/LevelTileMap.png";
	tilemapSettings.spriteSheetSize = DirectX::XMINT2(6, 6);
	tilemapSettings.animations = tilemapAnimations;
	tilemapSettings.position = DirectX::XMFLOAT2(40.0f, 20.0f);
	tilemapSettings.scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	tilemap = new Tilemap(tilemapSettings);

	CreateMario(DirectX::XMINT2(5, 11));
	CreateGoomba(DirectX::XMINT2(20, 11));
	CreateFlag(DirectX::XMINT2(198, 3), DirectX::XMINT2(198, 11));
}

World1L1::~World1L1()
{
	delete questionMarkBlock;
}

void World1L1::Update(const float deltaTime)
{
	Scene::Update(deltaTime);
}
