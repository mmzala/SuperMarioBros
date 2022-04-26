#include "TileCoinAction.h"
#include "../../../../Engine/SMBEngine.h" // Getting game
#include "../../../Game.h" // Getting ScoreTracker
#include "../../../Scoring/ScoreTracker.h" // Giving a coin / points
#include "../../../Data/ScoreData.h" // Data for scoring
#include "../Tilemap.h" // Setting tile

TileCoinAction::TileCoinAction(std::unordered_set<DirectX::XMINT2> tilePositions)
	:
	TileAction::TileAction(tilePositions)
{}

TileCoinAction::~TileCoinAction()
{}

void TileCoinAction::DoAction(Tilemap* tilemap, DirectX::XMINT2 tilemapPosition)
{
	tilemap->SetTile(tilemapPosition, 9);

	ScoreTracker* scoreTracker = SMBEngine::GetInstance()->GetGame()->GetScoreTracker();
	scoreTracker->AddCoin();
	scoreTracker->AddScore(ScoreData::CoinPickUp);
}
