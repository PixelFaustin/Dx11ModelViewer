#pragma once

#include <d3d11.h>

class TextureSampler
{
public:
	TextureSampler(ID3D11SamplerState* Sampler);
	~TextureSampler();

	ID3D11SamplerState* GetSampler() const;
private:
	ID3D11SamplerState* mSampler;
};

