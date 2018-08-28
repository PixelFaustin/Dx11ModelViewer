#pragma once

#include "ShaderFormat.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include <string>

class ShaderFactory
{
public:
	static void SetGlobalShaderPath(const WCHAR* ShaderPath);

	template<typename ShaderType>
	static ShaderType* CreateShader(std::string& Error, ID3D11Device* Device, const WCHAR* VSFilename, const WCHAR* PSFilename, const std::string& VSEntry, const std::string& PSEntry)
	{
		ID3D10Blob* VertexShaderBuffer;
		ID3D10Blob* ErrorBlob;
		std::wstring VSPath = std::wstring(sShaderPath) + std::wstring(VSFilename);
		HRESULT HR = D3DCompileFromFile(VSPath.c_str(), NULL, NULL, VSEntry.c_str(), "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &VertexShaderBuffer, &ErrorBlob);

		if (FAILED(HR))
		{
			Error = "Could not compile vertex shader";
			OutputShaderError(ErrorBlob);
			return nullptr;
		}

		ID3D10Blob* PixelShaderBuffer;
		std::wstring PSPath = std::wstring(sShaderPath) + std::wstring(PSFilename);
		HR = D3DCompileFromFile(PSPath.c_str(), NULL, NULL, PSEntry.c_str(), "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &PixelShaderBuffer, &ErrorBlob);

		if (FAILED(HR))
		{
			Error = "Could not compile pixel shader";
			OutputShaderError(ErrorBlob);
			VertexShaderBuffer->Release();
			PixelShaderBuffer->Release();
			return nullptr;
		}

		ID3D11VertexShader* VertexShader;
		ID3D11PixelShader*  PixelShader;

		HR = Device->CreateVertexShader(VertexShaderBuffer->GetBufferPointer(), VertexShaderBuffer->GetBufferSize(), NULL, &VertexShader);
		
		if (FAILED(HR))
		{
			Error = "Could not create vertex shader from bytecode";
			VertexShaderBuffer->Release();
			PixelShaderBuffer->Release();
			return nullptr;
		}

		HR = Device->CreatePixelShader(PixelShaderBuffer->GetBufferPointer(), PixelShaderBuffer->GetBufferSize(), NULL, &PixelShader);

		if (FAILED(HR))
		{
			Error = "Could not create pixel shader from bytecode";
			VertexShaderBuffer->Release();
			return nullptr;
		}

		ShaderType* Program = new ShaderType(VertexShader, PixelShader);
		auto Format = Program->GetFormat();

		ID3D11InputLayout* InputLayout;

		HR = Device->CreateInputLayout(Format->GetLayout(), Format->GetCount(), VertexShaderBuffer->GetBufferPointer(), VertexShaderBuffer->GetBufferSize(), &InputLayout);

		if (FAILED(HR))
		{
			Error = "Could not create input layout";
			VertexShaderBuffer->Release();
			PixelShaderBuffer->Release();
			return nullptr;
		}

		Program->SetInputLayout(InputLayout);
		
		if (!Program->Initialize(Device))
		{
			Error = "Could not initialize shader program";
			delete Program;
			return nullptr;
		}

		return Program;
	}
private:
	static void OutputShaderError(ID3D10Blob* Error);
	static const WCHAR* sShaderPath;
};

