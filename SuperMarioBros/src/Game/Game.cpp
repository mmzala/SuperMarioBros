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
	:
	camX(0.0f),
	camY(0.0f),
	speed(1200.0f)
{
	SpriteSettings* spriteSettings = new SpriteSettings();
	spriteSettings->textureFile = "assets/MarioSpriteSheet.png";
	spriteSettings->spriteSheetSize = 8;
	player = new Mario(spriteSettings);
	delete spriteSettings;
	player->transform->position = DirectX::XMFLOAT2(320.0f, 120.0f);
	player->transform->scale = DirectX::XMFLOAT2(1.25f, 1.25f);

	TilemapSettings tilemapSettings;
	tilemapSettings.spriteSheetFile = "assets/LevelTileMap.png";
	tilemapSettings.spriteSheetSize = 6;
	tilemapSettings.position = DirectX::XMFLOAT2(100.0f, 20.0f);
	tilemapSettings.scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	tilemap = new Tilemap(Worlds::world1d1, tilemapSettings);
}

Game::~Game()
{
	delete tilemap;
	delete player;
}

void Game::Update(float deltaTime)
{
	// Horizontal movement
	if (Input::GetInstance()->GetKey(DIK_A))
	{
		camX -= speed * deltaTime;
	}
	if (Input::GetInstance()->GetKey(DIK_D))
	{
		camX += speed * deltaTime;
	}

	DirectX::XMFLOAT2 newPosition = DirectX::XMFLOAT2(camX, camY);
	SMBEngine::GetInstance()->GetCamera()->SetPosition(newPosition);

	tilemap->Draw();
	player->Update(deltaTime);
}
