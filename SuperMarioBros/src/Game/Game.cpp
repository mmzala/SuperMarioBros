#include "Game.h"
#include <DirectXMath.h> // XMFLOAT2
#include <vector>

// Engine
#include "../Engine/SMBEngine.h" // Getting engine
#include "../Engine/Graphics/Camera.h" // Getting camera
#include "../Engine/Input/Input.h" // Checking input

// GameObject
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Transform.h" // Getting gameobject's transform

// World
#include "World/Tilemap.h"

// Physics
#include "../Engine/Physics/Collision.h" // Collision check
#include "../Engine/Physics/RectCollider.h" // Getting collider bounds

Game::Game()
	:
	playerX(300.0f),
	playerY(500.0f)
{
	object = new GameObject("assets/Earth1024x1024_256Frames.png");
	object->transform->scale = DirectX::XMFLOAT2(2.f, 2.f);

	object2 = new GameObject("assets/Earth1024x1024_256Frames.png");
	object2->transform->scale = DirectX::XMFLOAT2(3.f, 3.f);
	object2->transform->position = DirectX::XMFLOAT2(700.0f, 400.0f);

	std::vector<std::vector<int>> map = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	Tilemap::TilemapSettings tilemapSettings;
	tilemapSettings.spriteSheetFile = "assets/LevelTileMap.png";
	tilemapSettings.spriteSheetSize = 5;
	tilemapSettings.position = DirectX::XMFLOAT2(100.0f, 0.0f);
	tilemapSettings.scale = DirectX::XMFLOAT2(2.5f, 2.5f);

	tilemap = new Tilemap(map, tilemapSettings);
}

Game::~Game()
{
	delete object;
	delete object2;

	delete tilemap;
}

void Game::Update(float deltaTime)
{
	// Horizontal movement
	if (Input::GetInstance()->GetKey(DIK_A))
	{
		playerX -= 100.0f * deltaTime;
	}
	if (Input::GetInstance()->GetKey(DIK_D))
	{
		playerX += 100.0f * deltaTime;
	}

	// Vertical movement
	if (Input::GetInstance()->GetKey(DIK_W))
	{
		playerY += 100.0f * deltaTime;
	}
	if (Input::GetInstance()->GetKey(DIK_S))
	{
		playerY -= 100.0f * deltaTime;
	}

	tilemap->Draw();

	if (!Collision::Check(object->collider->GetBounds(), object2->collider->GetBounds()))
	{
		object2->Update(deltaTime);
	}

	object->transform->position = DirectX::XMFLOAT2(playerX, playerY);
	object->Update(deltaTime);
}
