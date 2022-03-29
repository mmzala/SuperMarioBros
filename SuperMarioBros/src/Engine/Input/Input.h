#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <xinput.h>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"xinput.lib")

class Input
{
public:
	Input(HWND hwnd);
	~Input();

	void Update();

	static Input* GetInstance();

	/// <summary>
	/// Checks if given key on the keyboard is currently pressed
	/// </summary>
	/// <param name="key"> What key to check </param>
	/// <returns> If key is pressed </returns>
	bool GetKey(int key);

	/// <summary>
	/// Gets the controller if it's connected
	/// </summary>
	/// <returns> Connected controller </returns>
	XINPUT_GAMEPAD* GetController();

private:
	void Initialize(HWND hwnd);

private:
	static Input* instance;

	LPDIRECTINPUT8 directInput;
	LPDIRECTINPUTDEVICE8 keyboard;
	char keyboardState[256];

	XINPUT_GAMEPAD controller;
};

