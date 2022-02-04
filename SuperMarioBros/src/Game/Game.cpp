#include "Game.h"
#include <DirectXMath.h> // XMFLOAT2
#include "GameObjects/GameObject.h"

Game::Game()
{
	object = new GameObject("assets/goomba.png");
	object->SetPosition(DirectX::XMFLOAT2(600.0f, 300.0f));
	//object->SetScale(DirectX::XMFLOAT2(1.5f, 3.0f));

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
	object->Update(deltaTime);
	object2->Update(deltaTime);
}
