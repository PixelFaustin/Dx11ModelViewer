#include "stdafx.h"
#include "StandardMeshShader.h"

using namespace DirectX;

StandardMeshShader::StandardMeshShader(ID3D11VertexShader * VertexShader, ID3D11PixelShader * PixelShader)
	: Shader(VertexShader, PixelShader)
{
}

StandardMeshShader::~StandardMeshShader()
{
}

bool StandardMeshShader::Initialize(ID3D11Device* Device)
{
	D3D11_BUFFER_DESC Desc{};
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.ByteWidth = sizeof(MatrixBuffer);
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.MiscFlags = 0;
	Desc.StructureByteStride = 0;

	return SUCCEEDED(Device->CreateBuffer(&Desc, NULL, &mMatrixBuffer));
}

void StandardMeshShader::SetParameters(ID3D11DeviceContext* Context, const SceneDescription& SceneDesc, const Texture2D* Textures, int TextureUnitCount) const
{
	D3D11_MAPPED_SUBRESOURCE MappedResource;

	XMMATRIX WorldMatrix = XMMatrixTranspose(SceneDesc.mWorldMatrix);
	XMMATRIX ViewMatrix = XMMatrixTranspose(SceneDesc.mCamera->GetViewMatrix());
	XMMATRIX ProjectionMatrix = XMMatrixTranspose(SceneDesc.mCamera->GetProjectionMatrix());

	Context->Map(mMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);

	MatrixBuffer* GPUData = reinterpret_cast<MatrixBuffer*>(MappedResource.pData);

	GPUData->World = WorldMatrix;
	GPUData->View = ViewMatrix;
	GPUData->Projection = ProjectionMatrix;

	Context->Unmap(mMatrixBuffer, 0);

	Context->VSSetConstantBuffers(0, 1, &mMatrixBuffer);

	if (TextureUnitCount > 0)
	{
		ID3D11ShaderResourceView* TextureView = Textures->GetShaderView();
		Context->PSSetShaderResources(0, 1, &TextureView);
	}
}
