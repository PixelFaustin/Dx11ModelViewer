#include "stdafx.h"
#include "Renderer.h"
#include "Color.h"

#define RELEASE(x) {if (x) { x->Release(); x = nullptr; }}

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
	RELEASE(mSwapChain);
	RELEASE(mDevice);
	RELEASE(mDeviceContext);
	RELEASE(mRenderTargetView);
	RELEASE(mDepthBuffer);
	RELEASE(mDepthStencilState);
	RELEASE(mDepthStencilView);
	RELEASE(mRasterState);
}

bool Renderer::Initialize(HWND Hwnd, int Width, int Height)
{
	mWidth = Width;
	mHeight = Height;

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Width = mWidth;
	SwapChainDesc.BufferDesc.Height = mHeight;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = Hwnd;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = 0;

	D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	HRESULT HR = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &FeatureLevel, 1, D3D11_SDK_VERSION, &SwapChainDesc, &mSwapChain, &mDevice, NULL, &mDeviceContext);

	if (FAILED(HR))
	{
		return false;
	}

	ID3D11Texture2D* BackBufferPtr;
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBufferPtr);
	mDevice->CreateRenderTargetView(BackBufferPtr, NULL, &mRenderTargetView);
	BackBufferPtr->Release();

	InitializeDefaultDepthBuffer();
	InitializeDefaultDepthState();
	InitializeDefaultRasterState();
	InitializeDefaultViewport();

	return true;
}

void Renderer::BeginScene(const Color& Col)
{
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, Col.GetRGBA());
	mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::RenderModel(const Camera& Cam, const Model& ModelToRender)
{
	BindStaticMesh(ModelToRender.GetMesh());

	const Material& Mat = ModelToRender.GetMaterial();
	const StandardMeshShader& Program = Mat.GetShader();

	Program.Bind(mDeviceContext);
	Mat.BindSampler(mDeviceContext);
	
	SceneDescription SceneDesc(&Cam);
	SceneDesc.mWorldMatrix = ModelToRender.GetModelTransform();

	Program.SetParameters(mDeviceContext, SceneDesc, Mat.GetTexture(), 1);

	mDeviceContext->DrawIndexed(ModelToRender.GetMesh().GetIndexCount(), 0, 0);
}

void Renderer::EndScene()
{
	mSwapChain->Present(0, 0);
}

ID3D11Device* Renderer::GetDevice()
{
	return mDevice;
}

void Renderer::BindStaticMesh(const StaticMesh& Mesh)
{
	unsigned int Stride = Mesh.GetVertexSize();
	unsigned int Offset = 0;

	const VertexBuffer* VB = Mesh.GetVertexBuffer();
	const IndexBuffer* IB = Mesh.GetIndexBuffer();

	ID3D11Buffer* VBuffer = VB->GetInternalBuffer();
	mDeviceContext->IASetVertexBuffers(0, 1, &VBuffer, &Stride, &Offset);

	mDeviceContext->IASetIndexBuffer(IB->GetInternalBuffer(), IB->GetIndexFormat(), 0);

	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST/*Mesh.GetTopology()*/);
}

void Renderer::InitializeDefaultDepthBuffer()
{
	D3D11_TEXTURE2D_DESC DepthBufferDesc;
	ZeroMemory(&DepthBufferDesc, sizeof(DepthBufferDesc));
	DepthBufferDesc.Width = mWidth;
	DepthBufferDesc.Height = mHeight;
	DepthBufferDesc.MipLevels = 1;
	DepthBufferDesc.ArraySize = 1;
	DepthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthBufferDesc.SampleDesc.Count = 1;
	DepthBufferDesc.SampleDesc.Quality = 0;
	DepthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthBufferDesc.CPUAccessFlags = 0;
	DepthBufferDesc.MiscFlags = 0;

	mDevice->CreateTexture2D(&DepthBufferDesc, NULL, &mDepthBuffer);
}

void Renderer::InitializeDefaultDepthState()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
	ZeroMemory(&DepthStencilViewDesc, sizeof(DepthStencilViewDesc));
	DepthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DepthStencilViewDesc.Texture2D.MipSlice = 0;

	mDevice->CreateDepthStencilView(mDepthBuffer, &DepthStencilViewDesc, &mDepthStencilView);
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
	ZeroMemory(&DepthStencilDesc, sizeof(DepthStencilDesc));
	DepthStencilDesc.DepthEnable = true;
	DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	DepthStencilDesc.StencilEnable = true;
	DepthStencilDesc.StencilReadMask = 0xFF;
	DepthStencilDesc.StencilWriteMask = 0xFF;
	DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	DepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	DepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	mDevice->CreateDepthStencilState(&DepthStencilDesc, &mDepthStencilState);
	mDevice->CreateDepthStencilState(&DepthStencilDesc, &mDepthStencilState);

	mDeviceContext->OMSetDepthStencilState(mDepthStencilState, 1);
}

void Renderer::InitializeDefaultRasterState()
{
	D3D11_RASTERIZER_DESC RasterDesc;
	ZeroMemory(&RasterDesc, sizeof(RasterDesc));
	RasterDesc.AntialiasedLineEnable = false;
	RasterDesc.CullMode = D3D11_CULL_BACK;
	RasterDesc.DepthBias = 0;
	RasterDesc.DepthBiasClamp = 0.0f;
	RasterDesc.DepthClipEnable = true;
	RasterDesc.FillMode = D3D11_FILL_SOLID;
	RasterDesc.FrontCounterClockwise = false;
	RasterDesc.MultisampleEnable = false;
	RasterDesc.ScissorEnable = false;
	RasterDesc.SlopeScaledDepthBias = 0.0f;

	mDevice->CreateRasterizerState(&RasterDesc, &mRasterState);
	mDeviceContext->RSSetState(mRasterState);
}

void Renderer::InitializeDefaultViewport()
{
	mViewport.Width = static_cast<float>(mWidth);
	mViewport.Height = static_cast<float>(mHeight);
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;
	mViewport.TopLeftX = 0.0f;
	mViewport.TopLeftY = 0.0f;

	mDeviceContext->RSSetViewports(1, &mViewport);
}
