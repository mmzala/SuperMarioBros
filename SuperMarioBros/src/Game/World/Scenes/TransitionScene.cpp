#include "TransitionScene.h"
#include "../../Game.h"
#include "../../GameObjects/Components/Transform.h"

// Mario sprite
#include "../../GameObjects/GameObject.h"
#include "../../../Engine/Graphics/Sprite.h"

// Getting remaining lives
#include "../../GameObjects/Mario.h"

// Setting up score tracker
#include "GameplayScene.h"

// UI
#include "../../../Engine/Graphics/UI/Canvas.h"
#include "../../../Engine/Graphics/UI/Text.h"

#include "../../../Engine/SMBEngine.h" // Getting engine
#include "../../../Engine/Graphics/Camera.h" // Calculating position in the middle of the screen
#include "../../../Engine/Graphics/DXManager.h" // Changing background color

TransitionScene::TransitionScene(Game* game)
	:
	Scene::Scene(game),
	graphics(SMBEngine::GetInstance()->GetGraphics()),
	mario(nullptr),
	canvas(nullptr),
	transitionToWorld(nullptr),
	transitionToScene(0),
	timeToTransition(0.0f)
{}

TransitionScene::~TransitionScene()
{}

void TransitionScene::Load()
{
	graphics->SetBackgroundColor(Colors::Black);

	// Setup score tracker if the next scene is a gameplay scene
	if (GameplayScene* scene = static_cast<GameplayScene*>(game->GetScene(transitionToScene)))
	{
		transitionToWorld = scene->GetWorldText();
		SetupScoreTracker(scene->GetWorldText(), scene->GetTimeToBeat(), true);
	}
	else
	{
		SetupScoreTracker("", 0.0f, true);
	}

	Scene::Load(); // We want to call CreateUI after we get transitionToWorld text
	Camera* camera = SMBEngine::GetInstance()->GetCamera();

	// Mario setup
	SpriteSettings marioSpriteSettings;
	marioSpriteSettings.textureFile = "assets/MarioSpriteSheet.png";
	marioSpriteSettings.spriteSheetSize = DirectX::XMINT2(7, 8);
	mario = new GameObject(marioSpriteSettings);
	mario->sprite->SetFrame(21);
	DirectX::XMFLOAT2 position = camera->GetViewportCenter();
	position.x -= 50.0f;
	mario->transform->position = position;
	mario->transform->scale = DirectX::XMFLOAT2(1.2f, 1.2f);
}

void TransitionScene::UnLoad()
{
	Scene::UnLoad();
	graphics->SetBackgroundColor(Colors::Blue);

	delete mario;
	delete canvas;
}

void TransitionScene::Update(const float deltaTime)
{
	Scene::Update(deltaTime);

	mario->Update(deltaTime);
	canvas->Update();

	timeToTransition -= deltaTime;
	if (timeToTransition < 0.0)
	{
		game->ChangeScene(transitionToScene);
	}
}

void TransitionScene::SetSceneToTransitionTo(int sceneIndex)
{
	transitionToScene = sceneIndex;
	timeToTransition = 3.5f;
}

void TransitionScene::CreateUI()
{
	Scene::CreateUI();

	TextSettings textSettings;
	textSettings.textureFile = "assets/Font.png";
	textSettings.spriteSheetSize = DirectX::XMINT2(16, 6);
	textSettings.minAsciiCode = 32;
	textSettings.maxAsciiCode = 126;
	textSettings.spacing = 2.0f;
	Text* livesText = new Text(textSettings);
	livesText->SetText(std::string("x ") + std::to_string(Mario::GetLives()));
	livesText->transform->position = DirectX::XMFLOAT2(0.0f, -25.0f);
	livesText->transform->scale = DirectX::XMFLOAT2(1.5f, 1.5f);
	
	Text* worldText = new Text(textSettings);
	if (transitionToWorld) worldText->SetText(std::string("World ") + transitionToWorld);
	worldText->transform->position = DirectX::XMFLOAT2(-120.0f, 50.0f);
	worldText->transform->scale = DirectX::XMFLOAT2(1.75f, 1.75f);

	canvas = new Canvas();
	canvas->AddElement(livesText);
	canvas->AddElement(worldText);
}
