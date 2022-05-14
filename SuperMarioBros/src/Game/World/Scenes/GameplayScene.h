#pragma once

#include "Scene.h"
#include <DirectXMath.h> // XMINT2
#include <vector>

class Game;
class Character;
class Mario;
class FireBall;
class Tilemap;
class Flag;
class AudioClip;

/// <summary>
/// Base scene that is used for gameplay
/// </summary>
class GameplayScene : public Scene
{
public:
	GameplayScene(Game* game, const char* worldText, const float timeToBeat);
	~GameplayScene() override;

	void Load() override;
	void UnLoad() override;
	void Update(const float deltaTime) override;

	void CreateMushroom(DirectX::XMINT2 tilemapPosition);
	void CreateFireFlower(DirectX::XMINT2 tilemapPosition);

	/// <summary>
	/// Spawns fire ball in given world position.
	/// </summary>
	/// <param name="worldPosition">: Position in the world to spawn fire ball </param>
	/// <param name="travelingDirectionRight">: If the fire ball should be traveling to the right </param>
	/// <returns> If succesfully spawned a fire ball </returns>
	bool SpawnFireBall(DirectX::XMFLOAT2 worldPosition, bool travelingDirectionRight);

	std::vector<Character*>& GetCharacters();
	const char* GetWorldText();
	float GetTimeToBeat();

protected:
	void CreateUI() override;
	void CreateMario(DirectX::XMINT2 tilemapPosition, DirectX::XMINT2 tilemapPolePositionBottom);
	void CreateGoomba(DirectX::XMINT2 tilemapPosition);
	void CreateGoombas(const std::vector<DirectX::XMINT2>& tilemapPositions);
	void CreateFlag(DirectX::XMINT2 tilemapPolePositionTop, DirectX::XMINT2 tilemapPolePositionBottom);
	void CreateFireBall();
	void CreateBackgroundMusic(const char* file);

private:
	void UpdateAllCharacters(float deltaTime);
	void DrawAllCharactersUpdateMario(float deltaTime);

protected:
	Tilemap* tilemap;
	Mario* player; // This does not have to be deleted (it gets deleted with characters vector)
	std::vector<Character*> characters;
	std::vector<FireBall*> fireBallsPool; // FireBalls are also a part of characters vector, so nothing here has to be deleted
	Flag* flag;

	AudioClip* backgroundMusic;

	const char* worldText;
	const float timeToBeat;
	float delayBeforeNextWorld;
};

