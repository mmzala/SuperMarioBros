#include "World1L1.h"
#include "../Data/Worlds.h"
#include "Tilemap.h"
#include "../../Engine/Graphics/UI/Text.h"
#include "../GameObjects/Components/Transform.h"

World1L1::World1L1()
	:
	Scene::Scene(),
	questionMarkBlock()
{}

World1L1::~World1L1()
{}

void World1L1::Load()
{
	Scene::Load();

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
	CreateGoomba(DirectX::XMINT2(22, 11));
	CreateFlag(DirectX::XMINT2(198, 3), DirectX::XMINT2(198, 11));

	TextSettings textSettings;
	textSettings.textureFile = "assets/Font.png";
	textSettings.spriteSheetSize = DirectX::XMINT2(16, 6);
	textSettings.minAsciiCode = 32;
	textSettings.maxAsciiCode = 126;
	textSettings.spacing = 0.0f;
	text = new Text(textSettings);
	text->SetText("MARIO");
	text->transform->position = DirectX::XMFLOAT2(200.0f, 200.0f);
	text->transform->scale = DirectX::XMFLOAT2(2.0f, 2.0f);
}

void World1L1::UnLoad()
{
	Scene::UnLoad();
	delete questionMarkBlock;
	delete text;
}

void World1L1::Update(const float deltaTime)
{
	Scene::Update(deltaTime);
	text->Draw();
}
