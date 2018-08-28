#pragma once

#include <d3d11.h>

template<size_t Count>
class ShaderFormat
{
public:
	ShaderFormat() = default;
	
	inline const D3D11_INPUT_ELEMENT_DESC* GetLayout() const
	{
		return Desc;
	}

	inline size_t GetCount() const
	{
		return Count;
	}
protected:
	D3D11_INPUT_ELEMENT_DESC Desc[Count];
};

class StandardShaderFormat : public ShaderFormat<3>
{
public:
	StandardShaderFormat();
};