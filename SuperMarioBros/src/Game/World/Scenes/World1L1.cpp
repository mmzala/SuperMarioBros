#include "World1L1.h"
#include "../../Game.h"
#include "../../GameObjects/Components/Transform.h"

// World
#include "../../Data/Worlds.h"
#include "../Tilemap/Tilemap.h"

// Tile actions
#include "../Tilemap/TileActions/TileSpawnPowerUpAction.h" // Spawning power up
#include "../Tilemap/TileActions/TileCoinAction.h" // Giving coins

World1L1::World1L1(Game* game)
	:
	GameplayScene::GameplayScene(game),
	questionMarkBlock(nullptr),
	spawnPowerUpAction(nullptr),
	giveCoinAction(nullptr)
{}

World1L1::~World1L1()
{}

void World1L1::Load()
{
	GameplayScene::Load();

	// Tilemap setup
	questionMarkBlock = new TilemapAnimation(6, 8, 0.8f);
	std::vector<TilemapAnimation*> tilemapAnimations = { questionMarkBlock };

	std::unordered_set<DirectX::XMINT2> spawnPowerUpTiles = { {20, 9} };
	spawnPowerUpAction = new TileSpawnPowerUpAction(spawnPowerUpTiles);

	std::unordered_set<DirectX::XMINT2> giveCoinTiles = { {15, 9}, {22, 9}, {21, 5} };
	giveCoinAction = new TileCoinAction(giveCoinTiles);

	std::vector<TileAction*> tileActions = { spawnPowerUpAction, giveCoinAction };

	TilemapSettings tilemapSettings;
	tilemapSettings.tilemap = Worlds::World1D1::Tilemap;
	tilemapSettings.collisionMap = Worlds::World1D1::Collisionmap;
	tilemapSettings.spriteSheetFile = "assets/LevelTileMap.png";
	tilemapSettings.spriteSheetSize = DirectX::XMINT2(6, 6);
	tilemapSettings.animations = tilemapAnimations;
	tilemapSettings.tileActions = tileActions;
	tilemapSettings.position = DirectX::XMFLOAT2(40.0f, 20.0f);
	tilemapSettings.scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	tilemap = new Tilemap(tilemapSettings);

	// Objects setup
	CreateMario(DirectX::XMINT2(2, 12), DirectX::XMINT2(198, 11));
	CreateGoombas(Worlds::World1D1::GoombaSpawnPoints);
	CreateFlag(DirectX::XMINT2(198, 3), DirectX::XMINT2(198, 11));

	// Scoring UI setup
	SetupScoreTracker("1-1", 400.0f, false);
}

void World1L1::UnLoad()
{
	GameplayScene::UnLoad();
	delete questionMarkBlock;
	delete spawnPowerUpAction;
	delete giveCoinAction;
}

void World1L1::Update(const float deltaTime)
{
	GameplayScene::Update(deltaTime);
}

void World1L1::CreateUI()
{
	GameplayScene::CreateUI();
}
