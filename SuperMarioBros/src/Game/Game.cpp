#include "Game.h"
#include <DirectXMath.h> // XMFLOAT2

// Engine
#include "../Engine/SMBEngine.h" // Getting engine
#include "../Engine/Graphics/Camera.h" // Getting camera
#include "../Engine/Input/Input.h" // Checking input

// GameObject
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Transform.h" // Getting gameobject's transform

// Physics
#include "../Engine/Physics/Collision.h" // Collision check
#include "../Engine/Physics/RectCollider.h" // Getting collider bounds

Game::Game()
	:
	playerX(100.0f),
	playerY(100.0f)
{
	object = new GameObject("assets/goomba.png");
	object->transform->scale = DirectX::XMFLOAT2(0.5f, 0.5f);

	object2 = new GameObject("assets/goomba.png");
	object2->transform->position = DirectX::XMFLOAT2(400.0f, 200.0f);
	object2->transform->scale = DirectX::XMFLOAT2(0.3f, 0.4f);

	object3 = new GameObject("assets/p3_front.png");
	object3->transform->position = DirectX::XMFLOAT2(500.0f, 500.0f);
	object3->transform->scale = DirectX::XMFLOAT2(0.6f, 0.6f);
}

Game::~Game()
{
	delete object;
	delete object2;
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

	object->transform->position = DirectX::XMFLOAT2(playerX, playerY);

	// If object1 is not colliding, then update object2
	if (!Collision::Check(object->collider->GetBounds(), object2->collider->GetBounds()))
	{
		object2->Update(deltaTime);
	}

	// If object1 is not colliding, then update object3
	if (!Collision::Check(object->collider->GetBounds(), object3->collider->GetBounds()))
	{
		object3->Update(deltaTime);
	}

	object->Update(deltaTime);
}
