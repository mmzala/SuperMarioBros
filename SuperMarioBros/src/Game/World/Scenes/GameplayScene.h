#pragma once

#include "Scene.h"
#include <DirectXMath.h> // XMINT2
#include <vector>

class Game;
class Character;
class Mario;
class Tilemap;
class Flag;

/// <summary>
/// Base scene that is used for gameplay
/// </summary>
class GameplayScene : public Scene
{
public:
	GameplayScene(Game* game);
	~GameplayScene() override;

	void Load() override;
	void UnLoad() override;
	void Update(const float deltaTime) override;

	void CreateMushroom(DirectX::XMINT2 tilemapPosition);
	std::vector<Character*>& GetCharacters();

protected:
	void CreateUI() override;
	void CreateMario(DirectX::XMINT2 tilemapPosition, DirectX::XMINT2 tilemapPolePositionBottom);
	void CreateGoomba(DirectX::XMINT2 tilemapPosition);
	void CreateGoombas(const std::vector<DirectX::XMINT2>& tilemapPositions);
	void CreateFlag(DirectX::XMINT2 tilemapPolePositionTop, DirectX::XMINT2 tilemapPolePositionBottom);

private:
	void UpdateAllCharacters(float deltaTime);
	void DrawAllCharactersUpdateMario(float deltaTime);

protected:
	Tilemap* tilemap;
	Mario* player; // This does not have to be deleted (it gets deleted with characters vector)
	std::vector<Character*> characters;
	Flag* flag;
};

