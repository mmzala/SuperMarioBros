#include "TileSpawnPowerUpAction.h"
#include "../../../Engine/SMBEngine.h" // Getting game
#include "../../Game.h" // Getting scene
#include "../Scenes/GameplayScene.h" // Spawning power up
#include "Tilemap.h" // Setting tile

TileSpawnPowerUpAction::TileSpawnPowerUpAction(std::unordered_set<DirectX::XMINT2> tilePositions)
	:
	TileAction::TileAction(tilePositions)
{}

TileSpawnPowerUpAction::~TileSpawnPowerUpAction()
{}

void TileSpawnPowerUpAction::DoAction(Tilemap* tilemap, DirectX::XMINT2 tilemapPosition)
{
	tilemap->SetTile(tilemapPosition, 9);
	tilemapPosition.y -= 2; // Setup position to spawn in

	GameplayScene* scene = (GameplayScene*)SMBEngine::GetInstance()->GetGame()->GetCurrentScene();
	scene->CreateMushroom(tilemapPosition);
}
