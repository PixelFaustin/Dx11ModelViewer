#pragma once

#include "Texture2D.h"
#include "TextureSampler.h"
#include "StandardMeshShader.h"

class Material
{
public:
	Material(StandardMeshShader* Program, Texture2D* Tex, TextureSampler* Sampler);
	~Material();

	const StandardMeshShader& GetShader() const;
	const Texture2D* GetTexture() const;

	void BindSampler(ID3D11DeviceContext* Context) const;
private:
	StandardMeshShader* mShader;
	Texture2D* mTexture;
	TextureSampler* mTextureSampler;
};

