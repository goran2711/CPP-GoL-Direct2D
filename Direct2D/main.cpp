#pragma comment(lib, "d2d1")
#pragma comment(lib, "windowscodecs")
#include <Windows.h>
#include "Graphics.h"

#include "GameController.h"
#include "Level1.h"

Graphics* graphics;

LRESULT CALLBACK WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// Passing on to default windows event handler
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmw, int nCmdShow)
{
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = L"MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"Game of Life", WS_OVERLAPPEDWINDOW, 100, 100,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!windowHandle) return -1;

	graphics = new Graphics();

	if (!graphics->init(windowHandle))
	{
		delete graphics;
		return -1;
	}

	GameLevel::init(graphics);

	ShowWindow(windowHandle, nCmdShow);

	GameController::init();
	GameController::loadInitialLevel(new Level1());

	MSG message;
	message.message = WM_NULL;

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);	// Send message to function defined by windowClass.lpfnWndProc = WindowProc;
		}
		else
		{
			GameController::update();
			
			graphics->beginDraw();
				GameController::render();
			graphics->endDraw();
		}
	}

	//MSG message;
	//while (GetMessage(&message, NULL, 0, 0))
	//{
	//	DispatchMessage(&message);
	//}

	delete graphics;

	return 0;
}