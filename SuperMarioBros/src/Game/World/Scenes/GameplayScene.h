#pragma once

#include "Scene.h"
#include <DirectXMath.h> // XMINT2
#include <vector>

class Game;
class Character;
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

	std::vector<Character*>& GetCharacters();

protected:
	void CreateUI() override;
	void CreateMario(DirectX::XMINT2 tilemapPosition);
	void CreateGoomba(DirectX::XMINT2 tilemapPosition);
	void CreateFlag(DirectX::XMINT2 tilemapPolePositionTop, DirectX::XMINT2 tilemapPolePositionBottom);
	void CreateMushroom(DirectX::XMINT2 tilemapPosition);

protected:
	Tilemap* tilemap;
	std::vector<Character*> characters;
	Flag* flag;
};

