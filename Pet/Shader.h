#pragma once

#include <d3d11.h>

template <typename ShaderFormatType>
class Shader
{
public:
	Shader(ID3D11VertexShader* VertexShader, ID3D11PixelShader* PixelShader);
	virtual ~Shader();

	inline const ShaderFormatType* GetFormat() const
	{
		return mFormat;
	}

	inline void SetInputLayout(ID3D11InputLayout* InputLayout)
	{
		mInputLayout = InputLayout;
	}

	void Bind(ID3D11DeviceContext* Context) const;
protected:
	ShaderFormatType* mFormat;

	ID3D11InputLayout* mInputLayout;

	ID3D11VertexShader* mVertexShader;
	ID3D11PixelShader* mPixelShader;
};

template <typename ShaderFormatType>
void Shader<ShaderFormatType>::Bind(ID3D11DeviceContext* Context) const
{
	Context->IASetInputLayout(mInputLayout);
	Context->VSSetShader(mVertexShader, NULL, 0);
	Context->PSSetShader(mPixelShader, NULL, 0);
}

template<typename ShaderFormatType>
inline Shader<ShaderFormatType>::Shader(ID3D11VertexShader* VertexShader, ID3D11PixelShader* PixelShader)
	: mVertexShader(VertexShader), mPixelShader(PixelShader)
{
	mFormat = new ShaderFormatType;
}

template<typename ShaderFormat>
inline Shader<ShaderFormat>::~Shader()
{
	if (mVertexShader)
	{
		mVertexShader->Release();
	}

	if (mPixelShader)
	{
		mPixelShader->Release();
	}

	if (mInputLayout)
	{
		mInputLayout->Release();
	}

	if (mFormat)
	{
		delete mFormat;
	}
}
