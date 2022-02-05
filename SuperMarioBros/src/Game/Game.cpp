#include "Game.h"
#include <DirectXMath.h> // XMFLOAT2
#include "GameObjects/GameObject.h"
#include "../Engine/SMBEngine.h" // Getting engine
#include "../Engine/Graphics/Camera.h" // Getting camera

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
	camPosX += 0.01f;
	SMBEngine::GetInstance()->GetCamera()->SetPosition(DirectX::XMFLOAT2(camPosX, 0.0f));

	object->Update(deltaTime);
	object2->Update(deltaTime);
}
