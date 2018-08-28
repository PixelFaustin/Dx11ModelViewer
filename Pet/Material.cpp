#include "stdafx.h"
#include "Material.h"


Material::Material(StandardMeshShader* Program, Texture2D* Tex, TextureSampler* Sampler)
	: mShader(Program), mTexture(Tex), mTextureSampler(Sampler)
{
}


Material::~Material()
{
	if (mShader)
	{
		delete mShader;
	}

	if (mTextureSampler)
	{
		delete mTextureSampler;
	}

	if (mTexture)
	{
		delete mTexture;
	}
}

const StandardMeshShader & Material::GetShader() const
{
	return *mShader;
}

const Texture2D* Material::GetTexture() const
{
	return mTexture;
}

void Material::BindSampler(ID3D11DeviceContext* Context) const
{
	ID3D11SamplerState* SS = mTextureSampler->GetSampler();
	Context->PSSetSamplers(0, 1, &SS);
}
