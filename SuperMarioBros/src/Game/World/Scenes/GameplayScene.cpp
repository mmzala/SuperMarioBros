#include "GameplayScene.h"
#include "../../Game.h"

// GameObjects
#include "../../GameObjects/Components/Transform.h"
#include "../../GameObjects/Mario.h"
#include "../../GameObjects/Goomba.h"
#include "../../GameObjects/Flag.h"
#include "../../GameObjects/Mushroom.h"
#include "../../GameObjects/FireFlower.h"
#include "../../GameObjects/OneUp.h"
#include "../../GameObjects/FireBall.h"

// World
#include "../Tilemap/Tilemap.h"

// Changing Scene
#include "../../../Engine/SMBEngine.h"
#include "../../../Engine/Input/Input.h"

// Scene Characters Update Mode
#include "../../../Engine/Graphics/Sprite.h"

// Converting remaining time to score after Mario is in castle
#include "../../Scoring/ScoreTracker.h"

// Background music
#include "../../../Engine/Audio/AudioClip.h"

GameplayScene::GameplayScene(Game* game, const char* worldText, const float timeToBeat)
	:
	Scene::Scene(game),
	tilemap(nullptr),
	player(nullptr),
	characters(),
	fireBallsPool(),
	flag(nullptr),
	backgroundMusic(nullptr),
	worldText(worldText),
	timeToBeat(timeToBeat),
	delayBeforeNextWorld(0.0f)
{}

GameplayScene::~GameplayScene()
{}

void GameplayScene::Load()
{
	Scene::Load();
	SetupScoreTracker(worldText, timeToBeat, false);
	delayBeforeNextWorld = 3.5f;
}

void GameplayScene::UnLoad()
{
	Scene::UnLoad();

	delete tilemap;
	delete flag;
	delete backgroundMusic;

	tilemap = 0;
	flag = 0;

	for (Character* character : characters)
	{
		delete character;
		character = 0;
	}
	characters.clear();
}

void GameplayScene::Update(const float deltaTime)
{
	if (Input::GetInstance()->GetKey(DIK_ESCAPE))
	{
		game->ChangeScene(Scenes::MainMenu);
	}

	tilemap->Update(deltaTime);
	flag->Update(deltaTime);
	
	switch (player->GetMarioState())
	{
	case MarioState::TouchedFlagPole:
		DrawAllCharactersUpdateMario(deltaTime);
		flag->moveDownwards = true;
		backgroundMusic->Stop();
		break;

	case MarioState::Dead:
		DrawAllCharactersUpdateMario(deltaTime);
		backgroundMusic->Stop();
		break;

	case MarioState::PowerUp:
		DrawAllCharactersUpdateMario(deltaTime);
		break;

	case MarioState::InCastle:
		DrawAllCharactersUpdateMario(deltaTime);
		if (game->GetScoreTracker()->ConvertTimeToScore(deltaTime))
		{
			delayBeforeNextWorld -= deltaTime;
			if (delayBeforeNextWorld < 0.0f)
			{
				int sceneIndex = game->GetSceneIndex() + 1;
				sceneIndex == Scenes::WinScene ? game->ChangeScene(sceneIndex) : game->TransitionToScene(sceneIndex);
			}
		}
		break;

	default:
		UpdateAllCharacters(deltaTime);
		break;
	}
}

void GameplayScene::CreateMushroom(const DirectX::XMINT2& tilemapPosition)
{
	SpriteSettings mushroomSpriteSettings = SpriteSettings();
	mushroomSpriteSettings.textureFile = "assets/Mushroom.png";
	mushroomSpriteSettings.spriteSheetSize = DirectX::XMINT2(1, 1);

	CharacterSettings mushroomSettings = CharacterSettings();
	mushroomSettings.spriteSettings = mushroomSpriteSettings;
	mushroomSettings.tilemap = tilemap;
	mushroomSettings.walkingSpeed = 150.0f;
	mushroomSettings.gravity = 450.0f;
	mushroomSettings.gravityAcceleration = 2700.0f;

	Mushroom* mushroom = new Mushroom(mushroomSettings);
	mushroom->transform->position = mushroom->GetSpawnPositionOnTile(tilemapPosition);
	mushroom->transform->scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	characters.push_back(mushroom);
}

void GameplayScene::CreateFireFlower(const DirectX::XMINT2& tilemapPosition)
{
	SpriteSettings fireFlowerSpriteSettings = SpriteSettings();
	fireFlowerSpriteSettings.textureFile = "assets/FireFlower.png";
	fireFlowerSpriteSettings.spriteSheetSize = DirectX::XMINT2(4, 1);

	CharacterSettings fireFlowerSettings = CharacterSettings();
	fireFlowerSettings.spriteSettings = fireFlowerSpriteSettings;
	fireFlowerSettings.tilemap = tilemap;
	fireFlowerSettings.walkingSpeed = 150.0f;
	fireFlowerSettings.gravity = 450.0f;
	fireFlowerSettings.gravityAcceleration = 2700.0f;

	FireFlower* fireFlower = new FireFlower(fireFlowerSettings);
	fireFlower->transform->position = fireFlower->GetSpawnPositionOnTile(tilemapPosition);
	fireFlower->transform->scale = DirectX::XMFLOAT2(2.0f, 2.0f);
	characters.push_back(fireFlower);
}

void GameplayScene::CreateOneUp(const DirectX::XMINT2& tilemapPosition)
{
	SpriteSettings oneUpSpriteSettings = SpriteSettings();
	oneUpSpriteSettings.textureFile = "assets/OneUp.png";
	oneUpSpriteSettings.spriteSheetSize = DirectX::XMINT2(1, 1);

	CharacterSettings oneUpSettings = CharacterSettings();
	oneUpSettings.spriteSettings = oneUpSpriteSettings;
	oneUpSettings.tilemap = tilemap;
	oneUpSettings.walkingSpeed = 150.0f;
	oneUpSettings.gravity = 450.0f;
	oneUpSettings.gravityAcceleration = 2700.0f;

	OneUp* oneUp = new OneUp(oneUpSettings);
	oneUp->transform->position = oneUp->GetSpawnPositionOnTile(tilemapPosition);
	oneUp->transform->scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	characters.push_back(oneUp);
}

bool GameplayScene::SpawnFireBall(DirectX::XMFLOAT2 worldPosition, bool travelingDirectionRight)
{
	for (FireBall* fireBall : fireBallsPool)
	{
		if (!fireBall->isInUse())
		{
			fireBall->SetInUse(true);
			fireBall->SetTravelingDirection(travelingDirectionRight);
			fireBall->transform->position = worldPosition;
			return true;
		}
	}

	return false;
}

std::vector<Character*>& GameplayScene::GetCharacters()
{
	return characters;
}

const char* GameplayScene::GetWorldText()
{
	return worldText;
}

float GameplayScene::GetTimeToBeat()
{
	return timeToBeat;
}

void GameplayScene::CreateUI()
{
	Scene::CreateUI();
}

void GameplayScene::CreateMario(DirectX::XMINT2 tilemapPosition, DirectX::XMINT2 tilemapPolePositionBottom)
{
	SpriteSettings marioSpriteSettings = SpriteSettings();
	marioSpriteSettings.textureFile = "assets/MarioSpriteSheet.png";
	marioSpriteSettings.spriteSheetSize = DirectX::XMINT2(7, 8);

	MovementComponentSettings movementSettings = MovementComponentSettings();
	movementSettings.runningSpeed = 350.0f;
	movementSettings.walkingAcceleration = 270.0f;
	movementSettings.runningAcceleration = 370.0f;
	movementSettings.releaseDeceleration = 150.0f;
	movementSettings.skiddingDeceleration = 450.0f;
	movementSettings.skidTurnaroundSpeed = 750.0f;
	movementSettings.runningDecelerationDelay = 0.25f;
	movementSettings.airWalkingTurnaroundSpeed = 750.0f;
	movementSettings.airRunningTurnaroundSpeed = 1050.0f;
	movementSettings.minJumpSpeed = 400.0f;
	movementSettings.maxJumpSpeed = 600.0f;
	movementSettings.maxJumpTime = 0.225f;
	movementSettings.jumpDecelaration = 2500.0f;

	MarioSettings marioSettings = MarioSettings();
	marioSettings.movementSettings = movementSettings;
	marioSettings.spriteSettings = marioSpriteSettings;
	marioSettings.tilemap = tilemap;
	marioSettings.walkingSpeed = 230.0f;
	marioSettings.gravity = 1000.0f;
	marioSettings.gravityAcceleration = 3500.0f;
	marioSettings.poweringUpTime = 0.8f;
	marioSettings.poweringDownTime = 1.0f;
	marioSettings.poweringDownFlickeringSpeed = 3.0f;
	marioSettings.flagPoleBottomPositionY = tilemap->GetPositionInWorldCoordinates(tilemapPolePositionBottom).y;
	marioSettings.poleDescendingSpeed = 0.5f;
	marioSettings.deathAnimationSpeed = 0.6f;
	marioSettings.timeBeforeDeathAnimation = 0.25f;
	marioSettings.timeAfterDeathBeforeSceneChange = 3.5f;

	player = new Mario(marioSettings);
	player->transform->position = player->GetSpawnPositionOnTile(tilemapPosition);
	player->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);
	characters.push_back(player);
}

void GameplayScene::CreateGoomba(DirectX::XMINT2 tilemapPosition)
{
	SpriteSettings goombaSpriteSettings = SpriteSettings();
	goombaSpriteSettings.textureFile = "assets/GoombaSpriteSheet.png";
	goombaSpriteSettings.spriteSheetSize = DirectX::XMINT2(3, 1);

	EnemySettings goombaSettings = EnemySettings();
	goombaSettings.spriteSettings = goombaSpriteSettings;
	goombaSettings.tilemap = tilemap;
	goombaSettings.walkingSpeed = 150.0f;
	goombaSettings.gravity = 450.0f;
	goombaSettings.gravityAcceleration = 2700.0f;
	goombaSettings.timeAfterDeath = 0.5f;

	Goomba* goomba = new Goomba(goombaSettings);
	goomba->transform->position = goomba->GetSpawnPositionOnTile(tilemapPosition);
	goomba->transform->scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	characters.push_back(goomba);
}

void GameplayScene::CreateGoombas(const std::vector<DirectX::XMINT2>& tilemapPositions)
{
	for (DirectX::XMINT2 position : tilemapPositions)
	{
		CreateGoomba(position);
	}
}

void GameplayScene::CreateFlag(DirectX::XMINT2 tilemapPolePositionTop, DirectX::XMINT2 tilemapPolePositionBottom)
{
	// There can only be 1 flag
	if (flag != nullptr) return;

	SpriteSettings flagSpriteSettings = SpriteSettings();
	flagSpriteSettings.textureFile = "assets/Flag.png";
	flagSpriteSettings.spriteSheetSize = DirectX::XMINT2(1, 1);

	FlagSettings flagSettings = FlagSettings();
	flagSettings.spriteSettings = flagSpriteSettings;
	flagSettings.poleTopPosition = tilemapPolePositionTop;
	flagSettings.poleBottomPosition = tilemapPolePositionBottom;
	flagSettings.descendingSpeed = 0.5f;

	flag = new Flag(flagSettings, tilemap);
	flag->transform->scale = DirectX::XMFLOAT2(2.2f, 2.2f);
}

void GameplayScene::CreateFireBall()
{
	SpriteSettings fireBallSpriteSettings = SpriteSettings();
	fireBallSpriteSettings.textureFile = "assets/FireBall.png";
	fireBallSpriteSettings.spriteSheetSize = DirectX::XMINT2(1, 1);

	CharacterSettings fireBallSettings = CharacterSettings();
	fireBallSettings.spriteSettings = fireBallSpriteSettings;
	fireBallSettings.tilemap = tilemap;
	fireBallSettings.walkingSpeed = 400.0f;
	fireBallSettings.gravity = 350.0f;
	fireBallSettings.gravityAcceleration = 2500.0f;

	FireBall* fireBall = new FireBall(fireBallSettings);
	fireBall->transform->scale = DirectX::XMFLOAT2(1.25f, 1.25f);

	characters.push_back(fireBall);
	fireBallsPool.push_back(fireBall);
}

void GameplayScene::CreateBackgroundMusic(const char* file)
{
	backgroundMusic = new AudioClip(file, true);
	backgroundMusic->Play();
}

void GameplayScene::UpdateAllCharacters(float deltaTime)
{
	for (size_t i = characters.size(); i-- > 0;)
	{
		if (!characters[i]->isActive) continue;
		characters[i]->Update(deltaTime);
	}
}

void GameplayScene::DrawAllCharactersUpdateMario(float deltaTime)
{
	for (size_t i = characters.size(); i-- > 1;) // Skip player
	{
		if (!characters[i]->isActive) continue;
		characters[i]->sprite->Draw(characters[i]->transform->GetWorldMatrix());
	}
	if(player->isActive) player->Update(deltaTime);
}
