#include "Game.h"
#include <DirectXMath.h> // XMFLOAT2

// Engine
#include "../Engine/SMBEngine.h" // Getting engine
#include "../Engine/Graphics/Camera.h" // Getting camera
#include "../Engine/Input/Input.h" // Checking input

// GameObject
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Transform.h" // Getting gameobject's transform

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
	Tilemap::TilemapSettings tilemapSettings;
	tilemapSettings.spriteSheetFile = "assets/LevelTileMap.png";
	tilemapSettings.spriteSheetSize = 5;
	tilemapSettings.position = DirectX::XMFLOAT2(100.0f, 20.0f);
	tilemapSettings.scale = DirectX::XMFLOAT2(2.5f, 2.5f);

	tilemap = new Tilemap(Worlds::world1, tilemapSettings);
}

Game::~Game()
{
	delete tilemap;
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
}
