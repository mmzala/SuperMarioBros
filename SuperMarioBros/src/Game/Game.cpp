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

// Settings
#include "Settings/CharacterSettings.h"
#include "Settings/SpriteSettings.h"

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
	CharacterSettings marioSettings = CharacterSettings();
	marioSettings.spriteSettings = marioSpriteSettings;
	marioSettings.tilemap = tilemap;
	marioSettings.movementSpeed = 500.0f;
	marioSettings.gravity = 150.0f;
	player = new Mario(marioSettings);
	player->transform->position = DirectX::XMFLOAT2(390.0f, 250.0f);
	player->transform->scale = DirectX::XMFLOAT2(1.0f, 1.0f);

	// Goomba setup
	SpriteSettings goombaSpriteSettings = SpriteSettings();
	goombaSpriteSettings.textureFile = "assets/GoombaSpriteSheet.png";
	goombaSpriteSettings.spriteSheetSize = DirectX::XMINT2(3, 1);
	CharacterSettings goombaSettings = CharacterSettings();
	goombaSettings.spriteSettings = goombaSpriteSettings;
	goombaSettings.tilemap = tilemap;
	goombaSettings.movementSpeed = 150.0f;
	goombaSettings.gravity = 150.0f;
	goomba = new Goomba(goombaSettings);
	goomba->transform->position = DirectX::XMFLOAT2(1200.0f, 200.0f);
	goomba->transform->scale = DirectX::XMFLOAT2(2.5f, 2.5f);
}

Game::~Game()
{
	delete tilemap;
	delete player;
	delete goomba;
}

void Game::Update(float deltaTime)
{
	tilemap->Draw();
	goomba->Update(deltaTime);
	player->Update(deltaTime);
}
