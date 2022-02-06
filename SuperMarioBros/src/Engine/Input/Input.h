#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "dinput8.lib")

class Input
{
public:
	Input(HWND hwnd);
	~Input();

	static Input* GetInstance();

	/// <summary>
	/// Checks if given key is currently pressed
	/// </summary>
	/// <param name="key"> What key to check </param>
	/// <returns> If key is pressed </returns>
	bool GetKey(int key);

private:
	void Initialize(HWND hwnd);

private:
	static Input* instance;

	LPDIRECTINPUT8 directInput;
	LPDIRECTINPUTDEVICE8 keyboard;
	char keyboardState[256];
};

