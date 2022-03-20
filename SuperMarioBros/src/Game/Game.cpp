#include "Game.h"
#include <DirectXMath.h> // XMFLOAT2

// Engine
#include "../Engine/SMBEngine.h" // Getting engine
#include "../Engine/Graphics/Camera.h" // Getting camera
#include "../Engine/Input/Input.h" // Checking input

// GameObjects
#include "GameObjects/Components/Transform.h" // Getting gameobject's transform
#include "GameObjects/Mario.h" // Player character
#include "GameObjects/Goomba.h" // Goomba enemy
#include "GameObjects/Flag.h" // Flag for the pole

// Settings
#include "Settings/MarioSettings.h"
#include "Settings/CharacterSettings.h"
#include "Settings/SpriteSettings.h"
#include "Settings/MovementComponentSettings.h"

// World
#include "World/Tilemap.h"
#include "Data/Worlds.h"

// Physics
#include "../Engine/Physics/Collision.h" // Collision check
#include "../Engine/Physics/RectCollider.h" // Getting collider bounds

Game::Game()
{
	// Tilemap setup
	TilemapSettings tilemapSettings;
	tilemapSettings.tilemap = Worlds::world1d1;
	tilemapSettings.collisionMap = Worlds::Collision::world1d1;
	tilemapSettings.spriteSheetFile = "assets/LevelTileMap.png";
	tilemapSettings.spriteSheetSize = DirectX::XMINT2(6, 6);
	tilemapSettings.position = DirectX::XMFLOAT2(40.0f, 20.0f);
	tilemapSettings.scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	tilemap = new Tilemap(tilemapSettings);

	// Mario setup
	SpriteSettings marioSpriteSettings = SpriteSettings();
	marioSpriteSettings.textureFile = "assets/MarioSpriteSheet.png";
	marioSpriteSettings.spriteSheetSize = DirectX::XMINT2(7, 8);
	MovementComponentSettings movementSettings = MovementComponentSettings();
	movementSettings.runningSpeed = 350.0f;
	movementSettings.walkingAcceleration = 0.3f;
	movementSettings.runningAcceleration = 0.35f;
	movementSettings.releaseDeceleration = 0.15f;
	movementSettings.skiddingDeceleration = 0.35f;
	movementSettings.skidTurnaroundSpeed = 0.7f;
	movementSettings.runningDecelerationDelay = 0.25f;
	movementSettings.airWalkingTurnaroundSpeed = 0.75f;
	movementSettings.airRunningTurnaroundSpeed = 0.85f;
	movementSettings.minJumpSpeed = 425.0f;
	movementSettings.maxJumpSpeed = 600.0f;
	movementSettings.maxJumpTime = 0.25f;
	movementSettings.jumpDecelaration = 1.5f;
	movementSettings.gravityAccelerationSpeed = 2.0f;
	MarioSettings marioSettings = MarioSettings();
	marioSettings.movementSettings = movementSettings;
	marioSettings.spriteSettings = marioSpriteSettings;
	marioSettings.tilemap = tilemap;
	marioSettings.walkingSpeed = 230.0f;
	marioSettings.gravity = 700.0f;
	player = new Mario(marioSettings);
	player->transform->position = DirectX::XMFLOAT2(7700.0f, 150.0f);
	player->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	// Goomba setup
	SpriteSettings goombaSpriteSettings = SpriteSettings();
	goombaSpriteSettings.textureFile = "assets/GoombaSpriteSheet.png";
	goombaSpriteSettings.spriteSheetSize = DirectX::XMINT2(3, 1);
	CharacterSettings goombaSettings = CharacterSettings();
	goombaSettings.spriteSettings = goombaSpriteSettings;
	goombaSettings.tilemap = tilemap;
	goombaSettings.walkingSpeed = 150.0f;
	goombaSettings.gravity = 150.0f;
	goomba = new Goomba(goombaSettings);
	goomba->transform->position = DirectX::XMFLOAT2(1000.0f, 200.0f);
	goomba->transform->scale = DirectX::XMFLOAT2(2.5f, 2.5f);

	// Flag setup
	SpriteSettings flagSpriteSettings = SpriteSettings();
	flagSpriteSettings.textureFile = "assets/Flag.png";
	flagSpriteSettings.spriteSheetSize = DirectX::XMINT2(1, 1);
	FlagSettings flagSettings = FlagSettings();
	flagSettings.spriteSettings = flagSpriteSettings;
	flagSettings.poleTopPosition = DirectX::XMINT2(198, 3);
	flagSettings.poleBottomPosition = DirectX::XMINT2(198, 11);
	flagSettings.descendingSpeed = 150.0f;
	flag = new Flag(flagSettings, tilemap);
	flag->transform->scale = DirectX::XMFLOAT2(2.2f, 2.2f);
}

Game::~Game()
{
	delete tilemap;
	delete player;
	delete goomba;
	delete flag;
}

void Game::Update(float deltaTime)
{
	tilemap->Draw();
	goomba->Update(deltaTime);
	player->Update(deltaTime);
	flag->Update(deltaTime);
}
