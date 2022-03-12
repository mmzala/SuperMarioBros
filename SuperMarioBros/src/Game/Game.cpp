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

// World
#include "World/Tilemap.h"
#include "World/Worlds.h"

// Physics
#include "../Engine/Physics/Collision.h" // Collision check
#include "../Engine/Physics/RectCollider.h" // Getting collider bounds

Game::Game()
{
	TilemapSettings tilemapSettings;
	tilemapSettings.tilemap = Worlds::world1d1;
	tilemapSettings.collisionMap = Worlds::Collision::world1d1;
	tilemapSettings.spriteSheetFile = "assets/LevelTileMap.png";
	tilemapSettings.spriteSheetSize.x = 6;
	tilemapSettings.spriteSheetSize.y = 6;
	tilemapSettings.position = DirectX::XMFLOAT2(40.0f, 20.0f);
	tilemapSettings.scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	tilemap = new Tilemap(tilemapSettings);

	SpriteSettings* spriteSettings = new SpriteSettings();
	spriteSettings->textureFile = "assets/MarioSpriteSheet.png";
	spriteSettings->spriteSheetSize.x = 7;
	spriteSettings->spriteSheetSize.y = 8;
	player = new Mario(spriteSettings, tilemap);
	delete spriteSettings;
	player->transform->position = DirectX::XMFLOAT2(390.0f, 250.0f);
	player->transform->scale = DirectX::XMFLOAT2(1.0f, 1.0f);
}

Game::~Game()
{
	delete tilemap;
	delete player;
}

void Game::Update(float deltaTime)
{
	tilemap->Draw();
	player->Update(deltaTime);
}
