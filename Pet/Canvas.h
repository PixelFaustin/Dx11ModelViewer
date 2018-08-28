#pragma once

#include "Color.h"
#include "Renderer.h"

class Canvas
{
public:
	Canvas(int DefaultWidth, int DefaultHeight);
	~Canvas();

	void InitializeWindow(HINSTANCE Instance, LPCWSTR AppName);
	bool InitializeRenderer();

	void SetVisible(bool bVisible);
	void SetForeground();
	void SetFocus();

	ID3D11Device* GetDevice();
	Renderer* GetRenderer();

	int GetClientWidth() const;
	int GetClientHeight() const;
private:
	Renderer* mRenderer;

	HWND mHWND;

	int mWidth;
	int mHeight;
};