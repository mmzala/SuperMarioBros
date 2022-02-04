#include "SMBEngine.h"
#include "Graphics/DXManager.h"
#include "../Game/Game.h"
#include "Graphics/Camera.h"

SMBEngine* SMBEngine::engine = nullptr;

SMBEngine::SMBEngine()
	:
	graphics(nullptr),
	game(nullptr),
	camera(nullptr)
{
	if (engine == nullptr)
	{
		engine = this;
	}
	else
	{
		MessageBox(NULL, L"Trying to create another engine, even though there is a instance already!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}
}

SMBEngine::~SMBEngine()
{
	delete camera;
	delete game;
	delete graphics;
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
}

void SMBEngine::Update()
{
	graphics->BeginFrame();
	game->Update(0.0f);
	graphics->EndFrame();
}

SMBEngine* SMBEngine::GetInstance()
{
	return engine;
}

DXManager* SMBEngine::GetGraphics()
{
	return graphics;
}

Camera* SMBEngine::GetCamera()
{
	return camera;
}
