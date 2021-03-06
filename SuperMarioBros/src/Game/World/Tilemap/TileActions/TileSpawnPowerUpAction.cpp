#include "TileSpawnPowerUpAction.h"
#include "../../../../Engine/SMBEngine.h" // Getting game
#include "../../../Game.h" // Getting scene
#include "../../Scenes/GameplayScene.h" // Spawning power up
#include "../Tilemap.h" // Setting tile
#include "../../../GameObjects/Mario.h" // Checking what power up to spawn
#include "../../../../Engine/Audio/AudioClip.h" // Audio

TileSpawnPowerUpAction::TileSpawnPowerUpAction(std::unordered_set<DirectX::XMINT2> tilePositions)
	:
	TileAction::TileAction(tilePositions),
	appearingPowerUpClip(new AudioClip("assets/AppearingPowerUp.wav", false))
{}

TileSpawnPowerUpAction::~TileSpawnPowerUpAction()
{
	delete appearingPowerUpClip;
}

void TileSpawnPowerUpAction::DoAction(Tilemap* tilemap, DirectX::XMINT2 tilemapPosition)
{
	tilemap->SetTile(tilemapPosition, 9);
	tilemapPosition.y -= 1; // Spawn above the hit tile

	GameplayScene* scene = (GameplayScene*)SMBEngine::GetInstance()->GetGame()->GetCurrentScene();
	Mario::GetPowerState() < MarioPowerState::Large ? scene->CreateMushroom(tilemapPosition) : scene->CreateFireFlower(tilemapPosition);
	appearingPowerUpClip->Play();
}
