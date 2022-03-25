#include "World1L1.h"
#include "../Data/Worlds.h"
#include "Tilemap.h"
#include "../../Engine/Graphics/UI/Text.h"
#include "../../Engine/Graphics/UI/Canvas.h"
#include "../GameObjects/Components/Transform.h"

World1L1::World1L1()
	:
	Scene::Scene(),
	questionMarkBlock(nullptr),
	canvas(nullptr),
	marioText(nullptr),
	scoreText(nullptr),
	coinCountText(nullptr),
	worldText(nullptr),
	worldCountText(nullptr),
	timeText(nullptr),
	timeCountText(nullptr)
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

	// Objects setup
	CreateMario(DirectX::XMINT2(5, 11));
	CreateGoomba(DirectX::XMINT2(22, 11));
	CreateFlag(DirectX::XMINT2(198, 3), DirectX::XMINT2(198, 11));	
}

void World1L1::UnLoad()
{
	Scene::UnLoad();
	delete questionMarkBlock;
	delete canvas;
}

void World1L1::Update(const float deltaTime)
{
	Scene::Update(deltaTime);
	canvas->Update();
}

void World1L1::CreateUI()
{
	TextSettings textSettings;
	textSettings.textureFile = "assets/Font.png";
	textSettings.spriteSheetSize = DirectX::XMINT2(16, 6);
	textSettings.minAsciiCode = 32;
	textSettings.maxAsciiCode = 126;
	textSettings.spacing = 2.5f;

	marioText = new Text(textSettings);
	marioText->SetText("MARIO");
	marioText->transform->position = DirectX::XMFLOAT2(-275.0f, 250.0f);
	marioText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	scoreText = new Text(textSettings);
	scoreText->SetText("000000");
	scoreText->transform->position = DirectX::XMFLOAT2(-275.0f, 225.0f);
	scoreText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	coinCountText = new Text(textSettings);
	coinCountText->SetText("x00");
	coinCountText->transform->position = DirectX::XMFLOAT2(-60.0f, 225.0f);
	coinCountText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	worldText = new Text(textSettings);
	worldText->SetText("WORLD");
	worldText->transform->position = DirectX::XMFLOAT2(70.0f, 250.0f);
	worldText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	worldCountText = new Text(textSettings);
	worldCountText->SetText("1-1");
	worldCountText->transform->position = DirectX::XMFLOAT2(90.0f, 225.0f);
	worldCountText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	timeText = new Text(textSettings);
	timeText->SetText("TIME");
	timeText->transform->position = DirectX::XMFLOAT2(220.0f, 250.0f);
	timeText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	timeCountText = new Text(textSettings);
	timeCountText->SetText("300");
	timeCountText->transform->position = DirectX::XMFLOAT2(220.0f, 225.0f);
	timeCountText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	canvas = new Canvas();
	canvas->AddElement(marioText);
	canvas->AddElement(scoreText);
	canvas->AddElement(coinCountText);
	canvas->AddElement(worldText);
	canvas->AddElement(worldCountText);
	canvas->AddElement(timeText);
	canvas->AddElement(timeCountText);
}
