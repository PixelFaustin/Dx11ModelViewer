#include "stdafx.h"
#include "SystemPlatform.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

SystemPlatform::SystemPlatform(LPCWSTR ApplicationName)
	: mApplicationName(ApplicationName)
{

}

SystemPlatform::~SystemPlatform()
{
	UnregisterClass(mApplicationName, mInstance);
}

bool SystemPlatform::Initialize()
{
	InitializePlatform();

	return true;
}

LRESULT SystemPlatform::MessageHandler(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	switch (UMsg)
	{
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		//InputHandler->KeyUp((unsigned int)WParam);
		break;
	default:
		return DefWindowProc(Hwnd, UMsg, WParam, LParam);
	}
}

void SystemPlatform::InitializePlatform()
{
	ApplicationHandle = this;

	mInstance = GetModuleHandle(NULL);

	WNDCLASSEX WC{};
	WC.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WC.lpfnWndProc = WndProc;
	WC.cbClsExtra = 0;
	WC.cbWndExtra = 0;
	WC.hInstance = mInstance;
	WC.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	WC.hIconSm = WC.hIcon;
	WC.hCursor = LoadCursor(NULL, IDC_ARROW);
	WC.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WC.lpszMenuName = NULL;
	WC.lpszClassName = mApplicationName;
	WC.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&WC);
}

void SystemPlatform::Run(Application* Application)
{
	if (!Application) { return; }

	bool Running = true;
	while (Running)
	{
		MSG Msg{};
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		if (Msg.message == WM_QUIT)
		{
			Running = false;
			break;
		}

		Running = Application->OnRun(1000.f / 60.f /* todo */);
	}
}


Canvas* SystemPlatform::CreateCanvas(int Width, int Height)
{
	Canvas* _Canvas = new Canvas(Width, Height);
	_Canvas->InitializeWindow(mInstance, mApplicationName);
	if (!_Canvas->InitializeRenderer())
	{
		return nullptr;
	}

	return _Canvas;
}

LRESULT CALLBACK WndProc(HWND Hwnd, UINT UMsg, WPARAM WParam, LPARAM LParam)
{
	switch (UMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return ApplicationHandle->MessageHandler(Hwnd, UMsg, WParam, LParam);
	}
}