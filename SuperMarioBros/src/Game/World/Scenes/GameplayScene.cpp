#include "GameplayScene.h"
#include "../../Game.h"

// GameObjects
#include "../../GameObjects/Components/Transform.h"
#include "../../GameObjects/Mario.h"
#include "../../GameObjects/Goomba.h"
#include "../../GameObjects/Flag.h"
#include "../../GameObjects/Mushroom.h"

// Settings
#include "../../Settings/MarioSettings.h"
#include "../../Settings/CharacterSettings.h"
#include "../../Settings/SpriteSettings.h"
#include "../../Settings/MovementComponentSettings.h"

// World
#include "../Tilemap/Tilemap.h"

// Changing Scene
#include "../../../Engine/SMBEngine.h"
#include "../../../Engine/Input/Input.h"

// Scene Characters Update Mode
#include "../../../Engine/Graphics/Sprite.h"

GameplayScene::GameplayScene(Game* game)
	:
	Scene::Scene(game),
	tilemap(nullptr),
	player(nullptr),
	characters(),
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
	delete flag;

	tilemap = 0;
	flag = 0;

	for (Character* character : characters)
	{
		delete character;
		character = 0;
	}
	characters.clear();
}

void GameplayScene::Update(const float deltaTime)
{
	if (Input::GetInstance()->GetKey(DIK_ESCAPE))
	{
		Game* game = SMBEngine::GetInstance()->GetGame();
		game->ChangeScene(0);
	}

	if (tilemap) tilemap->Update(deltaTime);
	if (flag) flag->Update(deltaTime);
	
	switch (player->GetMarioState())
	{
	case MarioState::PowerUp:
		for (size_t i = characters.size(); i-- > 1;) // Skip player
		{
			if (!characters[i]->isActive) continue;
			characters[i]->sprite->Draw(characters[i]->transform->GetWorldMatrix());
		}
		player->Update(deltaTime);
		break;

	default:
		for (size_t i = characters.size(); i-- > 0;)
		{
			if (!characters[i]->isActive) continue;
			characters[i]->Update(deltaTime);
		}
		break;
	}
}

void GameplayScene::CreateMushroom(DirectX::XMINT2 tilemapPosition)
{
	SpriteSettings mushroomSpriteSettings = SpriteSettings();
	mushroomSpriteSettings.textureFile = "assets/Mushroom.png";
	mushroomSpriteSettings.spriteSheetSize = DirectX::XMINT2(1, 1);

	CharacterSettings mushroomSettings = CharacterSettings();
	mushroomSettings.spriteSettings = mushroomSpriteSettings;
	mushroomSettings.tilemap = tilemap;
	mushroomSettings.walkingSpeed = 150.0f;
	mushroomSettings.gravity = 375.0f;

	Mushroom* mushroom = new Mushroom(mushroomSettings);
	mushroom->transform->position = tilemap->GetPositionInWorldCoordinates(tilemapPosition);
	mushroom->transform->scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	characters.push_back(mushroom);
}

std::vector<Character*>& GameplayScene::GetCharacters()
{
	return characters;
}

void GameplayScene::CreateUI()
{
	Scene::CreateUI();
}

void GameplayScene::CreateMario(DirectX::XMINT2 tilemapPosition)
{
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
	marioSettings.poweringUpTime = 1.5f;

	player = new Mario(marioSettings);
	player->transform->position = tilemap->GetPositionInWorldCoordinates(tilemapPosition);
	player->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);
	characters.push_back(player);
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
	goombaSettings.gravity = 375.0f;

	Goomba* goomba = new Goomba(goombaSettings);
	goomba->transform->position = tilemap->GetPositionInWorldCoordinates(tilemapPosition);
	goomba->transform->scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	characters.push_back(goomba);
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
