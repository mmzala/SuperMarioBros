#include "WinScene.h"
#include "../../Game.h"
#include "../../GameObjects/Components/Transform.h"

// UI
#include "../../../Engine/Graphics/UI/Canvas.h"
#include "../../../Engine/Graphics/UI/Text.h"

// Audio
#include "../../../Engine/Audio/AudioClip.h"

#include "../../../Engine/SMBEngine.h" // Getting graphics
#include "../../../Engine/Graphics/DXManager.h" // Changing background color
#include "../../../Engine/Input/Input.h" // Changing scene

WinScene::WinScene(Game* game)
	:
	Scene::Scene(game),
	graphics(SMBEngine::GetInstance()->GetGraphics()),
	canvas(nullptr),
	winClip(nullptr)
{}

WinScene::~WinScene()
{}

void WinScene::Load()
{
	Scene::Load();
	graphics->SetBackgroundColor(Colors::Black);
	winClip = new AudioClip("assets/YouWin.wav", false);
	winClip->Play();
}

void WinScene::UnLoad()
{
	Scene::UnLoad();
	graphics->SetBackgroundColor(Colors::Blue);

	delete canvas;
	delete winClip;
}

void WinScene::Update(const float deltaTime)
{
	Scene::Update(deltaTime);

	if (Input::GetInstance()->GetKey(DIK_SPACE))
	{
		game->ChangeScene(Scenes::MainMenu);
	}

	canvas->Update();
}

void WinScene::CreateUI()
{
	Scene::CreateUI();

	TextSettings textSettings;
	textSettings.textureFile = "assets/Font.png";
	textSettings.spriteSheetSize = DirectX::XMINT2(16, 6);
	textSettings.minAsciiCode = 32;
	textSettings.maxAsciiCode = 126;
	textSettings.spacing = 2.0f;
	Text* gameOverText = new Text(textSettings);
	gameOverText->SetText("You Win!");
	gameOverText->transform->position = DirectX::XMFLOAT2(-110.0f, 0.0f);
	gameOverText->transform->scale = DirectX::XMFLOAT2(1.75f, 1.75f);

	Text* pressSpaceText = new Text(textSettings);
	pressSpaceText->SetText("Press 'Space' to go to the main menu...");
	pressSpaceText->transform->position = DirectX::XMFLOAT2(-350.0f, -250.0f);
	pressSpaceText->transform->scale = DirectX::XMFLOAT2(1.0f, 1.0f);

	canvas = new Canvas();
	canvas->AddElement(gameOverText);
	canvas->AddElement(pressSpaceText);
}
