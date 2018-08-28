#pragma once

#include "Shader.h"
#include "ShaderFormat.h"
#include "SceneDescription.h"
#include "Texture2D.h"

#include <DirectXMath.h>

class StandardMeshShader : public Shader<StandardShaderFormat>
{
public:
	struct MatrixBuffer
	{
		DirectX::XMMATRIX World;
		DirectX::XMMATRIX View;
		DirectX::XMMATRIX Projection;
	};

	StandardMeshShader(ID3D11VertexShader* VertexShader, ID3D11PixelShader* PixelShader);
	~StandardMeshShader();

	bool Initialize(ID3D11Device* Device);
	void SetParameters(ID3D11DeviceContext* Context, const SceneDescription& SceneDesc, const Texture2D* Textures, int TextureUnitCount) const;
private:
	ID3D11Buffer* mMatrixBuffer;
};

