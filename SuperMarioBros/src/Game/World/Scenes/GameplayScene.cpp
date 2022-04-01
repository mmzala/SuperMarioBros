#include "GameplayScene.h"

// GameObjects
#include "../../GameObjects/Components/Transform.h" // Getting gameobject's transform
#include "../../GameObjects/Mario.h"
#include "../../GameObjects/Goomba.h"
#include "../../GameObjects/Flag.h"

// Settings
#include "../../Settings/MarioSettings.h"
#include "../../Settings/CharacterSettings.h"
#include "../../Settings/SpriteSettings.h"
#include "../../Settings/MovementComponentSettings.h"

// World
#include "../Tilemap.h"

// UI
#include "../../../Engine/Graphics/UI/Canvas.h"

// Changing Scene
#include "../../../Engine/SMBEngine.h"
#include "../../Game.h"
#include "../../../Engine/Input/Input.h"

GameplayScene::GameplayScene()
	:
	Scene::Scene(),
	tilemap(nullptr),
	player(nullptr),
	enemies(),
	flag(nullptr)
{}

GameplayScene::~GameplayScene()
{}

void GameplayScene::Load()
{
	Scene::Load();
}

void GameplayScene::UnLoad()
{
	Scene::UnLoad();

	delete tilemap;
	delete player;
	delete flag;

	tilemap = 0;
	player = 0; // This may be a small memory leak
	flag = 0;

	for (Character* enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();
}

void GameplayScene::Update(const float deltaTime)
{
	if (Input::GetInstance()->GetKey(DIK_ESCAPE))
	{
		Game* game = SMBEngine::GetInstance()->GetGame();
		game->ChangeScene(0);
	}

	if (tilemap) tilemap->Update(deltaTime);
	for (Character* enemy : enemies)
	{
		if (!enemy->IsInViewingFrustum()) continue;
		enemy->Update(deltaTime);
	}
	if (player) player->Update(deltaTime);
	if (flag) flag->Update(deltaTime);
}

void GameplayScene::CreateUI()
{
	Scene::CreateUI();
}

void GameplayScene::CreateMario(DirectX::XMINT2 tilemapPosition)
{
	// There can only be 1 mario
	if (player != nullptr) return;

	SpriteSettings marioSpriteSettings = SpriteSettings();
	marioSpriteSettings.textureFile = "assets/MarioSpriteSheet.png";
	marioSpriteSettings.spriteSheetSize = DirectX::XMINT2(7, 8);

	MovementComponentSettings movementSettings = MovementComponentSettings();
	movementSettings.runningSpeed = 350.0f;
	movementSettings.walkingAcceleration = 270.0f;
	movementSettings.runningAcceleration = 370.0f;
	movementSettings.releaseDeceleration = 150.0f;
	movementSettings.skiddingDeceleration = 450.0f;
	movementSettings.skidTurnaroundSpeed = 750.0f;
	movementSettings.runningDecelerationDelay = 0.25f;
	movementSettings.airWalkingTurnaroundSpeed = 750.0f;
	movementSettings.airRunningTurnaroundSpeed = 1050.0f;
	movementSettings.minJumpSpeed = 400.0f;
	movementSettings.maxJumpSpeed = 600.0f;
	movementSettings.maxJumpTime = 0.225f;
	movementSettings.jumpDecelaration = 2500.0f;
	movementSettings.gravityAccelerationSpeed = 3500.0f;

	MarioSettings marioSettings = MarioSettings();
	marioSettings.movementSettings = movementSettings;
	marioSettings.spriteSettings = marioSpriteSettings;
	marioSettings.tilemap = tilemap;
	marioSettings.walkingSpeed = 230.0f;
	marioSettings.gravity = 1000.0f;

	player = new Mario(marioSettings);
	player->transform->position = tilemap->GetPositionInWorldCoordinates(tilemapPosition);
	player->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);
}

void GameplayScene::CreateGoomba(DirectX::XMINT2 tilemapPosition)
{
	SpriteSettings goombaSpriteSettings = SpriteSettings();
	goombaSpriteSettings.textureFile = "assets/GoombaSpriteSheet.png";
	goombaSpriteSettings.spriteSheetSize = DirectX::XMINT2(3, 1);

	CharacterSettings goombaSettings = CharacterSettings();
	goombaSettings.spriteSettings = goombaSpriteSettings;
	goombaSettings.tilemap = tilemap;
	goombaSettings.walkingSpeed = 150.0f;
	goombaSettings.gravity = 150.0f;

	enemies.push_back(new Goomba(goombaSettings));
	enemies[enemies.size() - 1]->transform->position = tilemap->GetPositionInWorldCoordinates(tilemapPosition);
	enemies[enemies.size() - 1]->transform->scale = DirectX::XMFLOAT2(2.5f, 2.5f);
}

void GameplayScene::CreateFlag(DirectX::XMINT2 tilemapPolePositionTop, DirectX::XMINT2 tilemapPolePositionBottom)
{
	// There can only be 1 flag
	if (flag != nullptr) return;

	SpriteSettings flagSpriteSettings = SpriteSettings();
	flagSpriteSettings.textureFile = "assets/Flag.png";
	flagSpriteSettings.spriteSheetSize = DirectX::XMINT2(1, 1);

	FlagSettings flagSettings = FlagSettings();
	flagSettings.spriteSettings = flagSpriteSettings;
	flagSettings.poleTopPosition = tilemapPolePositionTop;
	flagSettings.poleBottomPosition = tilemapPolePositionBottom;
	flagSettings.descendingSpeed = 150.0f;

	flag = new Flag(flagSettings, tilemap);
	flag->transform->scale = DirectX::XMFLOAT2(2.2f, 2.2f);
}
