#include "stdafx.h"
#include "TextureSampler.h"


TextureSampler::TextureSampler(ID3D11SamplerState* Sampler)
	: mSampler(Sampler)
{
}


TextureSampler::~TextureSampler()
{
	if (mSampler)
	{
		mSampler->Release();
	}
}

ID3D11SamplerState* TextureSampler::GetSampler() const
{
	return mSampler;
}
