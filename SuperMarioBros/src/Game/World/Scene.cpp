#include "Scene.h"

// GameObjects
#include "../GameObjects/Components/Transform.h" // Getting gameobject's transform
#include "../GameObjects/Mario.h" // Player character
#include "../GameObjects/Goomba.h" // Goomba enemy
#include "../GameObjects/Flag.h" // Flag for the pole

// Settings
#include "../Settings/MarioSettings.h"
#include "../Settings/CharacterSettings.h"
#include "../Settings/SpriteSettings.h"
#include "../Settings/MovementComponentSettings.h"

// World
#include "Tilemap.h"

// Camera resetting
#include "../../Engine/SMBEngine.h"
#include "../../Engine/Graphics/Camera.h"

Scene::Scene()
	:
	tilemap(nullptr),
	player(nullptr),
	enemies(),
	flag(nullptr)
{}

Scene::~Scene()
{}

void Scene::Load()
{
	Camera* camera = SMBEngine::GetInstance()->GetCamera();
	camera->SetPosition(DirectX::XMFLOAT2(0.0f, 0.0f));
	CreateUI();
}

void Scene::UnLoad()
{
	// All of those 3 things need to be in a scene, so we don't need to check if they exist
	delete tilemap;
	delete player;
	delete flag;

	tilemap = 0;
	player = 0; // This may be a small memory leak
	flag = 0;

	for (Character* enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();
}

void Scene::Update(const float deltaTime)
{
	tilemap->Update(deltaTime);
	for (Character* enemy : enemies)
	{
		if (!enemy->IsInViewingFrustum()) continue;
		enemy->Update(deltaTime);
	}
	player->Update(deltaTime);
	flag->Update(deltaTime);
}

void Scene::CreateMario(DirectX::XMINT2 tilemapPosition)
{
	// There can only be 1 mario
	if (player != nullptr) return;

	SpriteSettings marioSpriteSettings = SpriteSettings();
	marioSpriteSettings.textureFile = "assets/MarioSpriteSheet.png";
	marioSpriteSettings.spriteSheetSize = DirectX::XMINT2(7, 8);
	MovementComponentSettings movementSettings = MovementComponentSettings();
	movementSettings.runningSpeed = 350.0f;
	movementSettings.walkingAcceleration = 0.3f;
	movementSettings.runningAcceleration = 0.35f;
	movementSettings.releaseDeceleration = 0.15f;
	movementSettings.skiddingDeceleration = 0.35f;
	movementSettings.skidTurnaroundSpeed = 0.7f;
	movementSettings.runningDecelerationDelay = 0.25f;
	movementSettings.airWalkingTurnaroundSpeed = 0.75f;
	movementSettings.airRunningTurnaroundSpeed = 0.85f;
	movementSettings.minJumpSpeed = 425.0f;
	movementSettings.maxJumpSpeed = 600.0f;
	movementSettings.maxJumpTime = 0.25f;
	movementSettings.jumpDecelaration = 1.5f;
	movementSettings.gravityAccelerationSpeed = 2.0f;
	MarioSettings marioSettings = MarioSettings();
	marioSettings.movementSettings = movementSettings;
	marioSettings.spriteSettings = marioSpriteSettings;
	marioSettings.tilemap = tilemap;
	marioSettings.walkingSpeed = 230.0f;
	marioSettings.gravity = 700.0f;
	player = new Mario(marioSettings);
	player->transform->position = tilemap->GetPositionInWorldCoordinates(tilemapPosition);
	player->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);
}

void Scene::CreateGoomba(DirectX::XMINT2 tilemapPosition)
{
	SpriteSettings goombaSpriteSettings = SpriteSettings();
	goombaSpriteSettings.textureFile = "assets/GoombaSpriteSheet.png";
	goombaSpriteSettings.spriteSheetSize = DirectX::XMINT2(3, 1);
	CharacterSettings goombaSettings = CharacterSettings();
	goombaSettings.spriteSettings = goombaSpriteSettings;
	goombaSettings.tilemap = tilemap;
	goombaSettings.walkingSpeed = 150.0f;
	goombaSettings.gravity = 150.0f;
	enemies.push_back(new Goomba(goombaSettings));
	enemies[enemies.size() - 1]->transform->position = tilemap->GetPositionInWorldCoordinates(tilemapPosition);
	enemies[enemies.size() - 1]->transform->scale = DirectX::XMFLOAT2(2.5f, 2.5f);
}

void Scene::CreateFlag(DirectX::XMINT2 tilemapPolePositionTop, DirectX::XMINT2 tilemapPolePositionBottom)
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
	flagSettings.descendingSpeed = 150.0f;
	flag = new Flag(flagSettings, tilemap);
	flag->transform->scale = DirectX::XMFLOAT2(2.2f, 2.2f);
}

void Scene::CreateUI()
{}
