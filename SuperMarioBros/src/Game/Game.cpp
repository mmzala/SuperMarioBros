#include "Game.h"
#include <DirectXMath.h> // XMFLOAT2

// Engine
#include "../Engine/SMBEngine.h" // Getting engine
#include "../Engine/Graphics/Camera.h" // Getting camera
#include "../Engine/Input/Input.h" // Checking input

// Graphics
#include "../Engine/Graphics/Sprite.h" // Sprite settings

// GameObject
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Transform.h" // Getting gameobject's transform
#include "GameObjects/Mario.h" // Player character
#include "GameObjects/Goomba.h" // Goomba enemy

// World
#include "World/Tilemap.h"
#include "Data/Worlds.h"

// Physics
#include "../Engine/Physics/Collision.h" // Collision check
#include "../Engine/Physics/RectCollider.h" // Getting collider bounds

Game::Game()
{
	TilemapSettings tilemapSettings;
	tilemapSettings.tilemap = Worlds::world1d1;
	tilemapSettings.collisionMap = Worlds::Collision::world1d1;
	tilemapSettings.spriteSheetFile = "assets/LevelTileMap.png";
	tilemapSettings.spriteSheetSize = DirectX::XMINT2(6, 6);
	tilemapSettings.position = DirectX::XMFLOAT2(40.0f, 20.0f);
	tilemapSettings.scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	tilemap = new Tilemap(tilemapSettings);

	SpriteSettings* pSpriteSettings = new SpriteSettings();
	pSpriteSettings->textureFile = "assets/MarioSpriteSheet.png";
	pSpriteSettings->spriteSheetSize = DirectX::XMINT2(7, 8);
	player = new Mario(pSpriteSettings, tilemap);
	delete pSpriteSettings;
	player->transform->position = DirectX::XMFLOAT2(390.0f, 250.0f);
	player->transform->scale = DirectX::XMFLOAT2(1.0f, 1.0f);

	SpriteSettings* gSpriteSettings = new SpriteSettings();
	gSpriteSettings->textureFile = "assets/GoombaSpriteSheet.png";
	gSpriteSettings->spriteSheetSize = DirectX::XMINT2(3, 1);
	goomba = new Goomba(gSpriteSettings, tilemap);
	delete gSpriteSettings;
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
