#include "TileAction.h"
#include "Tilemap.h"

TileAction::TileAction(std::unordered_set<DirectX::XMINT2> tilePositions)
    :
    actionTiles(tilePositions)
{}

TileAction::~TileAction()
{}

void TileAction::DoAction(Tilemap* tilemap, DirectX::XMINT2 tilemapPosition)
{}

std::unordered_set<DirectX::XMINT2> TileAction::GetActionTiles()
{
    return actionTiles;
}
