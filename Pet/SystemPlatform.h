#pragma once

#include "Application.h"
#include "Canvas.h"

class SystemPlatform
{
public:
	SystemPlatform(LPCWSTR ApplicationName);
	~SystemPlatform();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	void Run(Application* Application);

	bool Initialize();
	Canvas* CreateCanvas(int Width, int Height);
private:
	void InitializePlatform();
private:
	LPCWSTR mApplicationName;
	HINSTANCE mInstance;

	int mScreenHeight;
	int mScreenWidth;
};

static SystemPlatform* ApplicationHandle;
