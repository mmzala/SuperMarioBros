#pragma once

#include "Scene.h"
#include <DirectXMath.h> // XMINT2
#include <vector>

class Character;
class Mario;
class Goomba;
class Tilemap;
class Flag;

/// <summary>
/// Base scene that is used for gameplay
/// </summary>
class GameplayScene : public Scene
{
public:
	GameplayScene();
	~GameplayScene() override;

	void Load() override;
	void UnLoad() override;
	void Update(const float deltaTime) override;

protected:
	void CreateUI() override;
	void CreateMario(DirectX::XMINT2 tilemapPosition);
	void CreateGoomba(DirectX::XMINT2 tilemapPosition);
	void CreateFlag(DirectX::XMINT2 tilemapPolePositionTop, DirectX::XMINT2 tilemapPolePositionBottom);

protected:
	Tilemap* tilemap;
	Mario* player;
	std::vector<Character*> enemies;
	Flag* flag;
};

