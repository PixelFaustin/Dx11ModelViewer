#pragma once

#include "Texture2D.h"
#include "TextureSampler.h"

#include <string>
#include <d3d11.h>

class TextureFactory
{
public:
	static void SetGlobalTexturePath(const std::string& GlobalPath);
	static Texture2D* LoadTextureFromPNG(std::string& Error, ID3D11Device* Device, const std::string& Filepath, bool bGenMips = false);
	static TextureSampler* CreateSampler(std::string& Error, ID3D11Device* Device, D3D11_FILTER Filter, D3D11_TEXTURE_ADDRESS_MODE SMode, D3D11_TEXTURE_ADDRESS_MODE TMode);
private:
	static std::string sGlobalPath;
};

