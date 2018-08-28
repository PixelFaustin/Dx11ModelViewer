#include "stdafx.h"
#include "Texture2D.h"

Texture2D::Texture2D(ID3D11Texture2D * Texture, ID3D11ShaderResourceView * ResourceView)
	: mTexture(Texture), mTextureView(ResourceView)
{
}

Texture2D::~Texture2D()
{
	if (mTexture)
	{
		mTexture->Release();
	}

	if (mTextureView)
	{
		mTextureView->Release();
	}
}

ID3D11ShaderResourceView* Texture2D::GetShaderView() const
{
	return mTextureView;
}
