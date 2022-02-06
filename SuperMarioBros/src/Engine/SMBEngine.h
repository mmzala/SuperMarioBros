#pragma once

#include <Windows.h> // HWND

class DXManager;
class Game;
class Camera;
class Input;
class Shader;

class SMBEngine
{
public:
	SMBEngine(HWND hwnd);
	~SMBEngine();

	void Update();

	static SMBEngine* GetInstance();
	DXManager* GetGraphics();
	Camera* GetCamera();

	Shader* GetTextureShader();

private:
	void Initialize(HWND hwnd);

private:
	static SMBEngine* instance;

	DXManager* graphics;
	Game* game;
	Camera* camera;
	Input* input;

	Shader* textureShader;
};

