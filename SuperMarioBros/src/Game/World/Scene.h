#pragma once

#include <DirectXMath.h> // XMINT2
#include <vector>

class Character;
class Mario;
class Goomba;
class Tilemap;
class Flag;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(const float deltaTime);

protected:
	void CreateMario(DirectX::XMINT2 tilemapPosition);
	void CreateGoomba(DirectX::XMINT2 tilemapPosition);
	void CreateFlag(DirectX::XMINT2 tilemapPolePositionTop, DirectX::XMINT2 tilemapPolePositionBottom);
	virtual void CreateUI();

protected:
	Tilemap* tilemap;
	Mario* player;
	std::vector<Character*> enemies;
	Flag* flag;
};

