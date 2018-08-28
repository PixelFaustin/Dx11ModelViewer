#pragma once

#include "Color.h"
#include "Model.h"
#include "Camera.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include <Windows.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void BeginScene(const Color& Col);

	void RenderModel(const Camera& Cam, const Model& ModelToRender);

	void EndScene();

	ID3D11Device* GetDevice();

	bool Initialize(HWND Hwnd, int Width, int Height);
private:
	void BindStaticMesh(const StaticMesh& Mesh);

	void InitializeDefaultDepthBuffer();
	void InitializeDefaultDepthState();
	void InitializeDefaultRasterState();
	void InitializeDefaultViewport();
private:
	IDXGISwapChain * mSwapChain;
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mDeviceContext;
	ID3D11RenderTargetView* mRenderTargetView;

	ID3D11Texture2D* mDepthBuffer;
	ID3D11DepthStencilState* mDepthStencilState;
	ID3D11DepthStencilView* mDepthStencilView;
	ID3D11RasterizerState* mRasterState;

	D3D11_VIEWPORT mViewport;

	int mWidth;
	int mHeight;
};

