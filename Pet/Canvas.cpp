#include "stdafx.h"
#include "Canvas.h"

Canvas::Canvas(int DefaultWidth, int DefaultHeight)
	: mWidth(DefaultWidth), mHeight(DefaultHeight) {}

Canvas::~Canvas()
{
	if (mRenderer)
	{
		delete mRenderer;
	}
}

void Canvas::InitializeWindow(HINSTANCE Instance, LPCWSTR AppName)
{
	int PosX = (GetSystemMetrics(SM_CXSCREEN) - mWidth) / 2;
	int PosY = (GetSystemMetrics(SM_CYSCREEN) - mHeight) / 2;

	mHWND = CreateWindowEx(WS_EX_APPWINDOW, AppName, AppName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		PosX, PosY, mWidth, mHeight, NULL, NULL, Instance, NULL);
}

bool Canvas::InitializeRenderer()
{
	mRenderer = new Renderer;
	return mRenderer->Initialize(mHWND, mWidth, mHeight);
}

void Canvas::SetVisible(bool bVisible)
{
	ShowWindow(mHWND, bVisible ? SW_SHOW : SW_HIDE);
}

void Canvas::SetForeground()
{
	SetForegroundWindow(mHWND);
}

void Canvas::SetFocus()
{
	::SetFocus(mHWND);
}

ID3D11Device * Canvas::GetDevice()
{
	return GetRenderer()->GetDevice();
}

Renderer* Canvas::GetRenderer()
{
	return mRenderer;
}

int Canvas::GetClientWidth() const
{
	return mWidth;
}

int Canvas::GetClientHeight() const
{
	return mHeight;
}
