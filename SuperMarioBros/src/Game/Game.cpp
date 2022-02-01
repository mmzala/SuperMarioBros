#include "Game.h"
#include "../Graphics/DXManager.h"
#include "../Graphics/Sprite.h"

Game::Game(DXManager* graphics)
	:
	graphics(graphics)
{
	sprite = new Sprite("assets/goomba.png", graphics->GetDevice());
}

Game::~Game()
{
	delete sprite;
}

void Game::Update(float deltaTime)
{
	sprite->Draw(graphics->GetDeviceContext());
}
