#include "GameOverScene.h"
#include "../../Game.h"
#include "../../GameObjects/Components/Transform.h"

// UI
#include "../../../Engine/Graphics/UI/Canvas.h"
#include "../../../Engine/Graphics/UI/Text.h"

// Audio
#include "../../../Engine/Audio/AudioClip.h"

#include "../../../Engine/SMBEngine.h" // Getting graphics
#include "../../../Engine/Graphics/DXManager.h" // Changing background color

GameOverScene::GameOverScene(Game* game)
	:
	Scene::Scene(game),
	graphics(SMBEngine::GetInstance()->GetGraphics()),
	canvas(nullptr),
	gameOverClip(nullptr),
	timeToTransition(0.0f)
{}

GameOverScene::~GameOverScene()
{}

void GameOverScene::Load()
{
	Scene::Load();
	graphics->SetBackgroundColor(Colors::Black);

	gameOverClip = new AudioClip("assets/GameOver.wav", false);
	gameOverClip->Play();
	timeToTransition = 4.5f;
}

void GameOverScene::UnLoad()
{
	Scene::UnLoad();
	graphics->SetBackgroundColor(Colors::Blue);

	delete canvas;
	delete gameOverClip;
}

void GameOverScene::Update(const float deltaTime)
{
	Scene::Update(deltaTime);

	canvas->Update();

	timeToTransition -= deltaTime;
	if (timeToTransition < 0.0f)
	{
		game->ChangeScene(Scenes::MainMenu);
	}
}

void GameOverScene::CreateUI()
{
	Scene::CreateUI();

	TextSettings textSettings;
	textSettings.textureFile = "assets/Font.png";
	textSettings.spriteSheetSize = DirectX::XMINT2(16, 6);
	textSettings.minAsciiCode = 32;
	textSettings.maxAsciiCode = 126;
	textSettings.spacing = 2.0f;
	Text* gameOverText = new Text(textSettings);
	gameOverText->SetText("Game Over");
	gameOverText->transform->position = DirectX::XMFLOAT2(-120.0f, 0.0f);
	gameOverText->transform->scale = DirectX::XMFLOAT2(1.75f, 1.75f);

	canvas = new Canvas();
	canvas->AddElement(gameOverText);
}
