#include "stdafx.h"
#include "ModelViewerApplication.h"
#include "ShaderFactory.h"
#include "MeshFactory.h"
#include "TextureFactory.h"
#include "TextureSampler.h"
#include "FBXWrapper.h"

#include <iostream>
#include <vector>

ModelViewerApplication::ModelViewerApplication(Canvas * _Canvas)
	: Application(_Canvas)
{

}

ModelViewerApplication::~ModelViewerApplication()
{
	if (mTriangleModel)
	{
		delete mTriangleModel;
	}
	
	if (mCamera)
	{
		delete mCamera;
	}
}

bool ModelViewerApplication::Initialize()
{
	std::string Errors = {};
	ShaderFactory::SetGlobalShaderPath(L"C:\\Users\\Austin\\Desktop\\assets\\shaders\\");
	TextureFactory::SetGlobalTexturePath("C:\\Users\\Austin\\Desktop\\assets\\textures\\");
	MeshFactory::SetGlobalPath("C:\\Users\\Austin\\Desktop\\assets\\meshes\\");

	FBXWrapper FBX;
	FBX.Initialize();
	std::string Error{};
	mLoadedMesh = MeshFactory::LoadOBJFromFile(Errors, mCanvas->GetDevice(), "suzanne.obj");

	mTriangleModel = CreateTriangleModel();
	if (!mTriangleModel)
	{
		return false;
	}

	mCamera = new Camera(DirectX::XMFLOAT3(0.f, 0.f, -600.f), DirectX::XMFLOAT3(0.f, 0.f, 1.f), DirectX::XMFLOAT3(0.f, 1.f, 0.f));
	float Aspect = static_cast<float>(mCanvas->GetClientWidth()) / static_cast<float>(mCanvas->GetClientHeight());
	mCamera->InitializeProjection(45.f, Aspect, 0.1f, 1000.f);

	return true;
}

StaticMesh* ModelViewerApplication::CreateTriangleMesh() const
{
	std::vector<DirectX::XMFLOAT3> Positions = { DirectX::XMFLOAT3(-1.f, -1.f, 0.f), DirectX::XMFLOAT3(0.f, 1.0f, 0.f), DirectX::XMFLOAT3(1.f, -1.f, 0.f) };
	std::vector<DirectX::XMFLOAT3> Normals = { DirectX::XMFLOAT3(0.f, 0.f, 1.f), DirectX::XMFLOAT3(0.f, 0.f, 1.f), DirectX::XMFLOAT3(0.f, 0.f, 1.f) };
	std::vector<DirectX::XMFLOAT2> UV0 = { DirectX::XMFLOAT2(0.f, 1.f), DirectX::XMFLOAT2(0.5f, 0.f), DirectX::XMFLOAT2(1.f, 1.f) };
	std::vector<unsigned int> Indices = { 0, 1, 2 };

	return MeshFactory::CreateMesh(mCanvas->GetDevice(), Positions, Normals, UV0, Indices);
}

Model* ModelViewerApplication::CreateTriangleModel() const
{
	std::string Errors{};

	StandardMeshShader* Program = ShaderFactory::CreateShader<StandardMeshShader>(Errors, mCanvas->GetDevice(), L"default-vs.hlsl", L"default-ps.hlsl", "VertexEntryMain", "PixelEntryMain");
	if (!Program)
	{
		std::cerr << Errors << std::endl;
		return nullptr;
	}

	StaticMesh* Triangle = mLoadedMesh;//CreateTriangleMesh();
	if (!Triangle)
	{
		std::cerr << "Could not create triangle mesh!" << std::endl;
		delete Program;
		return nullptr;
	}

	Texture2D* BrickTexture = TextureFactory::LoadTextureFromPNG(Errors, mCanvas->GetDevice(), "brick.png", false);
	if (!BrickTexture)
	{
		std::cerr << Errors << std::endl;
		delete Program;
		delete Triangle;
		return nullptr;
	}

	TextureSampler* Sampler = TextureFactory::CreateSampler(Errors, mCanvas->GetDevice(), D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP);
	if (!Sampler)
	{
		std::cerr << Errors << std::endl;
		delete Program;
		delete Triangle;
		delete BrickTexture;
		return nullptr;
	}

	Material* TriangleMaterial = new Material(Program, BrickTexture, Sampler);

	Model* TriangleModel = new Model("Triangle");
	TriangleModel->SetMaterial(TriangleMaterial);
	TriangleModel->SetMesh(Triangle);

	return TriangleModel;
}

void ModelViewerApplication::Update(float DeltaTime)
{
	mCamera->Update(DeltaTime);
}

void ModelViewerApplication::Render(Renderer* _Renderer)
{
	_Renderer->BeginScene(Color(1.f, 0.f, 0.f, 1.f));

	_Renderer->RenderModel(*mCamera, *mTriangleModel);

	_Renderer->EndScene();
}

bool ModelViewerApplication::OnRun(float DeltaTime)
{
	Update(DeltaTime);
	Render(mCanvas->GetRenderer());

	return true;
}
