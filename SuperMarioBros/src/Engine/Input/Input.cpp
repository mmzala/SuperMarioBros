#include "Input.h"

Input* Input::instance = nullptr;

Input::Input(HWND hwnd)
	:
	directInput(NULL),
	keyboard(NULL),
	keyboardState(),
	controller()
{
	if (instance == nullptr)
	{
		instance = this;
	}
	else
	{
		MessageBox(NULL, L"Trying to create another input manager, even though there is a instance already!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}

	Initialize(hwnd);
}

Input::~Input()
{
	if (keyboard)
	{
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = 0;
	}

	if (directInput) directInput->Release();
	directInput = 0;
}

void Input::Update()
{
	// Update keyboard state
	keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	// Update controller state
	ZeroMemory(&controller, sizeof(XINPUT_STATE));

	XINPUT_STATE state;
	DWORD result = XInputGetState(0, &state);

	if (result == 0) controller = state.Gamepad;
}

Input* Input::GetInstance()
{
	return instance;
}

bool Input::GetKey(int key)
{
	return (keyboardState[key] & 0x80);
}

XINPUT_GAMEPAD* Input::GetController()
{
	return &controller;
}

void Input::Initialize(HWND hwnd)
{
	// Initialize DirectInput object
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&directInput, NULL);

	if (FAILED(result))
	{
		MessageBox(NULL, L"Failed to create direct input!", L"Error!", MB_OK);
		PostQuitMessage(0);
		return;
	}

	// Initialize the keyboard
	directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	keyboard->SetDataFormat(&c_dfDIKeyboard);
	keyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	keyboard->Acquire();
}


