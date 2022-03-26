#include "Scene.h"

#include "../../GameObjects/Components/Transform.h"

// UI
#include "../../../Engine/Graphics/UI/Text.h"
#include "../../../Engine/Graphics/UI/UISprite.h"
#include "../../../Engine/Graphics/UI/Canvas.h"

// Camera resetting
#include "../../../Engine/SMBEngine.h"
#include "../../../Engine/Graphics/Camera.h"

Scene::Scene()
	:
	gameCanvas(nullptr),
	marioText(nullptr),
	scoreText(nullptr),
	coinCountText(nullptr),
	worldText(nullptr),
	worldCountText(nullptr),
	timeText(nullptr),
	timeCountText(nullptr),
	coinSprite(nullptr)
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
	delete gameCanvas;
}

void Scene::Update(const float deltaTime)
{}

void Scene::CreateUI()
{
	TextSettings textSettings;
	textSettings.textureFile = "assets/Font.png";
	textSettings.spriteSheetSize = DirectX::XMINT2(16, 6);
	textSettings.minAsciiCode = 32;
	textSettings.maxAsciiCode = 126;
	textSettings.spacing = 2.0f;

	marioText = new Text(textSettings);
	marioText->SetText("MARIO");
	marioText->transform->position = DirectX::XMFLOAT2(-275.0f, 250.0f);
	marioText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	scoreText = new Text(textSettings);
	scoreText->SetText("000000");
	scoreText->transform->position = DirectX::XMFLOAT2(-275.0f, 225.0f);
	scoreText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	coinCountText = new Text(textSettings);
	coinCountText->SetText("x00");
	coinCountText->transform->position = DirectX::XMFLOAT2(-60.0f, 225.0f);
	coinCountText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	worldText = new Text(textSettings);
	worldText->SetText("WORLD");
	worldText->transform->position = DirectX::XMFLOAT2(70.0f, 250.0f);
	worldText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	worldCountText = new Text(textSettings);
	worldCountText->SetText("1-1");
	worldCountText->transform->position = DirectX::XMFLOAT2(90.0f, 225.0f);
	worldCountText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	timeText = new Text(textSettings);
	timeText->SetText("TIME");
	timeText->transform->position = DirectX::XMFLOAT2(220.0f, 250.0f);
	timeText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	timeCountText = new Text(textSettings);
	timeCountText->SetText("300");
	timeCountText->transform->position = DirectX::XMFLOAT2(220.0f, 225.0f);
	timeCountText->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);

	UISpriteSettings spriteSettings;
	spriteSettings.textureFile = "assets/UICoins.png";
	spriteSettings.spriteSheetSize = DirectX::XMINT2(3, 1);
	spriteSettings.animation = Animation(0, 2, 5.0f);

	coinSprite = new UISprite(spriteSettings);
	coinSprite->transform->position = DirectX::XMFLOAT2(-80.0f, 225.0f);
	coinSprite->transform->scale = DirectX::XMFLOAT2(1.5f, 1.5f);

	gameCanvas = new Canvas();
	gameCanvas->AddElement(marioText);
	gameCanvas->AddElement(scoreText);
	gameCanvas->AddElement(coinCountText);
	gameCanvas->AddElement(worldText);
	gameCanvas->AddElement(worldCountText);
	gameCanvas->AddElement(timeText);
	gameCanvas->AddElement(timeCountText);
	gameCanvas->AddElement(coinSprite);
}
