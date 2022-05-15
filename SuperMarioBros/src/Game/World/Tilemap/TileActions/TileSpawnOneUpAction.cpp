#include "TileSpawnOneUpAction.h"
#include "../../../../Engine/SMBEngine.h" // Getting game
#include "../../../Game.h" // Getting scene
#include "../../Scenes/GameplayScene.h" // Spawning power up
#include "../Tilemap.h" // Setting tile
#include "../../../../Engine/Audio/AudioClip.h" // Audio

TileSpawnOneUpAction::TileSpawnOneUpAction(std::unordered_set<DirectX::XMINT2> tilePositions)
	:
	TileAction::TileAction(tilePositions),
	appearingOneUpClip(new AudioClip("assets/AppearingPowerUp.wav", false))
{}

TileSpawnOneUpAction::~TileSpawnOneUpAction()
{
	delete appearingOneUpClip;
}

void TileSpawnOneUpAction::DoAction(Tilemap* tilemap, DirectX::XMINT2 tilemapPosition)
{
	tilemap->SetTile(tilemapPosition, 9);
	tilemapPosition.y -= 1; // Spawn above the hit tile

	GameplayScene* scene = (GameplayScene*)SMBEngine::GetInstance()->GetGame()->GetCurrentScene();
	scene->CreateOneUp(tilemapPosition);
	appearingOneUpClip->Play();
}
