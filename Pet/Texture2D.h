#pragma once

#include <d3d11.h>

class Texture2D
{
public:
	Texture2D(ID3D11Texture2D* Texture, ID3D11ShaderResourceView* ResourceView);
	~Texture2D();

	ID3D11ShaderResourceView* GetShaderView() const;
private:
	ID3D11Texture2D* mTexture;
	ID3D11ShaderResourceView* mTextureView;
};

