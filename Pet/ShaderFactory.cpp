#include "stdafx.h"
#include "ShaderFactory.h"

#include <fstream>

void ShaderFactory::OutputShaderError(ID3D10Blob* Error)
{
	char* compileErrors;
	unsigned long long bufferSize, i;
	std::ofstream fout;


	compileErrors = (char*)(Error->GetBufferPointer());

	bufferSize = Error->GetBufferSize();

	fout.open("shader-error.txt");

	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();

	Error->Release();
}

const WCHAR* ShaderFactory::sShaderPath;

void ShaderFactory::SetGlobalShaderPath(const WCHAR* ShaderPath)
{
	ShaderFactory::sShaderPath = ShaderPath;
}
