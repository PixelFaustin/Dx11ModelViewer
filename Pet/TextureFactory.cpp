#include "stdafx.h"
#include "TextureFactory.h"

#include <d3d11.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string TextureFactory::sGlobalPath;

ID3D11ShaderResourceView* CreateTextureResourceView(ID3D11Device* Device, ID3D11Texture2D* Texture, const D3D11_SHADER_RESOURCE_VIEW_DESC* Desc)
{
	ID3D11ShaderResourceView* SRV;
	
	return (FAILED(Device->CreateShaderResourceView(Texture, Desc, &SRV))) ? nullptr : SRV;
}

void TextureFactory::SetGlobalTexturePath(const std::string & GlobalPath)
{
	TextureFactory::sGlobalPath = GlobalPath;
}

Texture2D* TextureFactory::LoadTextureFromPNG(std::string& Error, ID3D11Device* Device, const std::string& Filepath, bool bGenMips)
{
	int Width = 0;
	int Height = 0;
	int ChannelCount = 0;

	unsigned char* Data = stbi_load((sGlobalPath + Filepath).c_str(), &Width, &Height, &ChannelCount, 4);

	if (!Data)
	{
		Error = "Could not load image from filepath";
		return nullptr;
	}

	D3D11_TEXTURE2D_DESC Desc{};
	Desc.Width = Width;
	Desc.Height = Height;
	Desc.MipLevels = bGenMips ? 0 : 1;
	Desc.ArraySize = 1;
	Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Usage = D3D11_USAGE_IMMUTABLE;
	Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA SubresData{};
	SubresData.pSysMem = Data;
	SubresData.SysMemPitch = Width * 4;
	SubresData.SysMemSlicePitch = 0;

	ID3D11Texture2D* TexturePtr;
	HRESULT HR = Device->CreateTexture2D(&Desc, &SubresData, &TexturePtr);
	stbi_image_free(Data);
	
	if (FAILED(HR))
	{
		Error = "Could not create texture from loaded image file";
		return nullptr;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = bGenMips ? 0 : 1;

	ID3D11ShaderResourceView* RV = CreateTextureResourceView(Device, TexturePtr, &SRVDesc);
	if (!RV)
	{
		Error = "Could not create texture resource view";
		TexturePtr->Release();
		return nullptr;
	}

	return new Texture2D(TexturePtr, RV);
}

TextureSampler * TextureFactory::CreateSampler(std::string& Error, ID3D11Device* Device, D3D11_FILTER Filter, D3D11_TEXTURE_ADDRESS_MODE SMode, D3D11_TEXTURE_ADDRESS_MODE TMode)
{
	D3D11_SAMPLER_DESC Desc{};
	Desc.Filter = Filter;
	Desc.AddressU = SMode;
	Desc.AddressV = TMode;
	Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.MipLODBias = 0.0f;
	Desc.MaxAnisotropy = 1;
	Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	Desc.BorderColor[0] = 0;
	Desc.BorderColor[1] = 0;
	Desc.BorderColor[2] = 0;
	Desc.BorderColor[3] = 0;
	Desc.MinLOD = 0;
	Desc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* SState;

	if (FAILED(Device->CreateSamplerState(&Desc, &SState)))
	{
		Error = "Could not create sampler state";
		return nullptr;
	}

	return new TextureSampler(SState);
}
