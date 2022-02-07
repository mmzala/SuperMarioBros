#include "SMBEngine.h"
#include "Graphics/DXManager.h"
#include "../Game/Game.h"
#include "Graphics/Camera.h"
#include "Input/Input.h"
#include "../Utils/Timer.h"
#include "Graphics/Shaders/Shader.h"

SMBEngine* SMBEngine::instance = nullptr;

SMBEngine::SMBEngine(HWND hwnd)
	:
	graphics(nullptr),
	game(nullptr),
	camera(nullptr),
	input(nullptr),
	timer(nullptr),
	textureShader(nullptr)
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
	delete graphics;

	delete textureShader;
}

void SMBEngine::Update()
{
	float deltaTime = timer->Mark();

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

Camera* SMBEngine::GetCamera()
{
	return camera;
}

Shader* SMBEngine::GetTextureShader()
{
	return textureShader;
}

void SMBEngine::Initialize(HWND hwnd)
{
	RECT dimensions;
	GetClientRect(hwnd, &dimensions);

	const unsigned int clientWidth = dimensions.right - dimensions.left;
	const unsigned int clientHeight = dimensions.bottom - dimensions.top;

	graphics = new DXManager(hwnd, clientWidth, clientHeight);
	game = new Game();
	camera = new Camera(clientWidth, clientHeight);
	input = new Input(hwnd);
	timer = new Timer();

	textureShader = new Shader(L"src/Engine/Graphics/Shaders/Precompiled/VertexShader.cso",
		L"src/Engine/Graphics/Shaders/Precompiled/PixelShader.cso");
}
