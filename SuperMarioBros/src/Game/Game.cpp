#include "Game.h"
#include <DirectXMath.h> // XMFLOAT2
#include "GameObjects/GameObject.h"
#include "../Engine/SMBEngine.h" // Getting engine
#include "../Engine/Graphics/Camera.h" // Getting camera
#include "../Engine/Input/Input.h" // Checking input

Game::Game()
	:
	camPosX(0.0f)
{
	object = new GameObject("assets/goomba.png");
	object->SetPosition(DirectX::XMFLOAT2(600.0f, 300.0f));
	object->SetScale(DirectX::XMFLOAT2(0.5f, 0.5f));

	object2 = new GameObject("assets/p3_front.png");
	object2->SetPosition(DirectX::XMFLOAT2(400.0f, 200.0f));
	object2->SetRotation(2.0f);
}

Game::~Game()
{
	delete object;
	delete object2;
}

void Game::Update(float deltaTime)
{
	if (Input::GetInstance()->GetKey(DIK_A) || Input::GetInstance()->GetController()->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		camPosX -= 100.0 * deltaTime;
	}
	if (Input::GetInstance()->GetKey(DIK_D) || Input::GetInstance()->GetController()->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		camPosX += 100.0 * deltaTime;
	}
	
	SMBEngine::GetInstance()->GetCamera()->SetPosition(DirectX::XMFLOAT2(camPosX, 0.0f));

	object->Update(deltaTime);
	object2->Update(deltaTime);
}
