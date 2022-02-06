#include <Windows.h>
#include <memory>
#include "Engine/SMBEngine.h"
#include "Game/Game.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &paintStruct);
		EndPaint(hwnd, &paintStruct);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nShowCmd);

	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = L"SMB";

	if (!RegisterClassEx(&wndClass))
	{
		return -1;
	}

	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_EX_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindowA("SMB", "Super Mario Bros", WS_EX_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, hInstance, NULL);

	if (!hwnd)
	{
		return -1;
	}

	ShowWindow(hwnd, nShowCmd);

	std::auto_ptr<SMBEngine> engine(new SMBEngine(hwnd));

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			engine->Update();
		}
	}

	return static_cast<int>(msg.wParam);
}