#include "SMBEngine.h"
#include "Graphics/DXManager.h"
#include "Audio/AudioManager.h"
#include "../Game/Game.h"
#include "Graphics/Camera.h"
#include "Input/Input.h"
#include "../Utils/Timer.h"
#include "Graphics/Shaders/Shader.h"

SMBEngine* SMBEngine::instance = nullptr;

SMBEngine::SMBEngine(HWND hwnd)
	:
	graphics(nullptr),
	camera(nullptr),
	input(nullptr),
	audioManager(nullptr),
	timer(nullptr),
	game(nullptr),
	spriteShader(nullptr),
	deltaTime(0.0f)
{
	if (instance == nullptr)
	{
		instance = this;
	}
	else
	{
		MessageBox(NULL, L"Trying to create another engine, even though there is a instance already!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}

	Initialize(hwnd);
}

SMBEngine::~SMBEngine()
{
	delete timer;
	delete input;
	delete camera;
	delete game;
	delete audioManager;
	delete graphics;

	delete spriteShader;
}

void SMBEngine::Update()
{
	deltaTime = timer->Mark();

	input->Update();
	graphics->BeginFrame();
	game->Update(deltaTime);
	graphics->EndFrame();
}

SMBEngine* SMBEngine::GetInstance()
{
	return instance;
}

DXManager* SMBEngine::GetGraphics()
{
	return graphics;
}

AudioManager* SMBEngine::GetAudioManager()
{
	return audioManager;
}

Camera* SMBEngine::GetCamera()
{
	return camera;
}

Game* SMBEngine::GetGame()
{
	return game;
}

Shader* SMBEngine::GetSpriteShader()
{
	return spriteShader;
}

float SMBEngine::GetDeltaTime()
{
	return deltaTime;
}

void SMBEngine::Initialize(HWND hwnd)
{
	RECT dimensions;
	GetClientRect(hwnd, &dimensions);

	const unsigned int clientWidth = dimensions.right - dimensions.left;
	const unsigned int clientHeight = dimensions.bottom - dimensions.top;

	graphics = new DXManager(hwnd, clientWidth, clientHeight);
	audioManager = new AudioManager();
	camera = new Camera(clientWidth, clientHeight);
	input = new Input(hwnd);
	timer = new Timer();
	game = new Game();

	spriteShader = new Shader(L"assets/SpriteVS.cso", L"assets/SpritePS.cso");

	// Set graphics settings for primitive type
	ID3D11DeviceContext* deviceContext = graphics->GetDeviceContext();
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set graphics settings for shaders
	deviceContext->IASetInputLayout(spriteShader->GetInputLayout());
	deviceContext->VSSetShader(spriteShader->GetVertexShader(), 0, 0);
	deviceContext->PSSetShader(spriteShader->GetPixelShader(), 0, 0);
}
