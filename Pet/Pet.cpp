#include "stdafx.h"
#include "SystemPlatform.h"
#include "ModelViewerApplication.h"
#include "Shader.h"

#include <Windows.h>

#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	const int WindowWidth = 1280;
	const int WindowHeight = 720;

	SystemPlatform* Platform = new SystemPlatform(L"Pet");
	if (!Platform ->Initialize())
	{
		std::cerr << "Could not initialize Windows platform!" << std::endl;
		return 1;
	}

	Canvas* AppCanvas = Platform->CreateCanvas(WindowWidth, WindowHeight);
	if (!AppCanvas)
	{
		std::cerr << "Could not create canvas!" << std::endl;
		return 1;
	}

	AppCanvas->SetVisible(true);
	AppCanvas->SetForeground();
	AppCanvas->SetFocus();

	ModelViewerApplication* App = new ModelViewerApplication(AppCanvas);
	if (!App->Initialize())
	{
		std::cerr << "Could not initialize app!";
		return 1;
	}

	Platform->Run(App);

	delete Platform;
	delete App;

	return 0;
}
