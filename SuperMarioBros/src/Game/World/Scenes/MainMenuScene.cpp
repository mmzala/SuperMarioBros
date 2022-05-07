#include "MainMenuScene.h"
#include "../../Game.h"
#include "../../GameObjects/Components/Transform.h"

// World
#include "../../Data/Worlds.h"
#include "../Tilemap/Tilemap.h"

// UI
#include "../../../Engine/Graphics/UI/Canvas.h"
#include "../../../Engine/Graphics/UI/Text.h"
#include "../../../Engine/Graphics/UI/UISprite.h"

// Mario object
#include "../../GameObjects/GameObject.h"

// Changing Scene
#include "../../../Engine/SMBEngine.h"
#include "../../../Engine/Input/Input.h"

MainMenuScene::MainMenuScene(Game* game)
	:
	Scene::Scene(game),
	tilemap(nullptr),
	questionMarkBlock(nullptr),
	mario(nullptr),
	mainMenuCanvas(nullptr)
{}

MainMenuScene::~MainMenuScene()
{}

void MainMenuScene::Load()
{
	Scene::Load();

	// Tilemap setup
	questionMarkBlock = new TilemapAnimation(6, 8, 0.8f);
	std::vector<TilemapAnimation*> tilemapAnimations = { questionMarkBlock };
	TilemapSettings tilemapSettings;
	tilemapSettings.tilemap = Worlds::World1D1::Tilemap;
	tilemapSettings.collisionMap = Worlds::World1D1::Collisionmap;
	tilemapSettings.spriteSheetFile = "assets/LevelTileMap.png";
	tilemapSettings.spriteSheetSize = DirectX::XMINT2(6, 6);
	tilemapSettings.animations = tilemapAnimations;
	tilemapSettings.position = DirectX::XMFLOAT2(20.0f, 20.0f);
	tilemapSettings.scale = DirectX::XMFLOAT2(2.5f, 2.5f);
	tilemap = new Tilemap(tilemapSettings);

	// Mario setup
	SpriteSettings marioSpriteSettings;
	marioSpriteSettings.textureFile = "assets/MarioSpriteSheet.png";
	marioSpriteSettings.spriteSheetSize = DirectX::XMINT2(7, 8);
	mario = new GameObject(marioSpriteSettings);
	mario->sprite->SetFrame(21);
	mario->transform->position = tilemap->GetPositionInWorldCoordinates(DirectX::XMINT2(2, 11));
	mario->transform->position.y -= 22.0f; // Calculate this properly later
	mario->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	SetupScoreTracker("1-1", 0.0f, true, true, true);
}

void MainMenuScene::UnLoad()
{
	Scene::UnLoad();
	delete tilemap;
	delete questionMarkBlock;
	delete mario;
	delete mainMenuCanvas;
}

void MainMenuScene::Update(const float deltaTime)
{
	Scene::Update(deltaTime);

	if (Input::GetInstance()->GetKey(DIK_RETURN)) // Enter key
	{
		Game* game = SMBEngine::GetInstance()->GetGame();
		game->TransitionToScene(Scenes::World1d1);
	}

	tilemap->Update(deltaTime);
	mario->Update(deltaTime);
	mainMenuCanvas->Update();
}

void MainMenuScene::CreateUI()
{
	Scene::CreateUI();

	UISpriteSettings optionCursorSettings;
	optionCursorSettings.textureFile = "assets/OptionCursor.png";
	optionCursorSettings.spriteSheetSize = DirectX::XMINT2(1, 1);
	UISprite* optionCursor = new UISprite(optionCursorSettings);
	optionCursor->transform->position = DirectX::XMFLOAT2(-160.0f, -50.0f);
	optionCursor->transform->scale = DirectX::XMFLOAT2(2.0f, 2.0f);

	UISpriteSettings titleSettings;
	titleSettings.textureFile = "assets/Title.png";
	titleSettings.spriteSheetSize = DirectX::XMINT2(1, 1);
	UISprite* title = new UISprite(titleSettings);
	title->transform->position.y = 100.0f;
	title->transform->scale = DirectX::XMFLOAT2(2.5f, 2.5f);

	TextSettings textSettings;
	textSettings.textureFile = "assets/Font.png";
	textSettings.spriteSheetSize = DirectX::XMINT2(16, 6);
	textSettings.minAsciiCode = 32;
	textSettings.maxAsciiCode = 126;
	textSettings.spacing = 2.0f;
	Text* playText = new Text(textSettings);
	playText->SetText("Start Game");
	playText->transform->position = DirectX::XMFLOAT2(-120.0f, -50.0f);
	playText->transform->scale = DirectX::XMFLOAT2(1.5f, 1.5f);

	mainMenuCanvas = new Canvas();
	mainMenuCanvas->AddElement(optionCursor);
	mainMenuCanvas->AddElement(title);
	mainMenuCanvas->AddElement(playText);
}
