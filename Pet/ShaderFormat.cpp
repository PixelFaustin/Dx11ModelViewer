#include "stdafx.h"
#include "ShaderFormat.h"

StandardShaderFormat::StandardShaderFormat()
{
	Desc[0].SemanticName = "POSITION";
	Desc[0].SemanticIndex = 0;
	Desc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	Desc[0].InputSlot = 0;
	Desc[0].AlignedByteOffset = 0;
	Desc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Desc[0].InstanceDataStepRate = 0;

	Desc[1].SemanticName = "NORMAL";
	Desc[1].SemanticIndex = 0;
	Desc[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	Desc[1].InputSlot = 0;
	Desc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	Desc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Desc[1].InstanceDataStepRate = 0;
	
	Desc[2].SemanticName = "TEXCOORD";
	Desc[2].SemanticIndex = 0;
	Desc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	Desc[2].InputSlot = 0;
	Desc[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	Desc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Desc[2].InstanceDataStepRate = 0;
}
