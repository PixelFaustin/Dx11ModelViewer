#pragma once

#include <d3d11.h>

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	static IndexBuffer* Create(ID3D11Device* Device, unsigned int* Indices, size_t Count);

	ID3D11Buffer* GetInternalBuffer() const;

	inline DXGI_FORMAT GetIndexFormat() const
	{
		return DXGI_FORMAT_R32_UINT;
	}

	unsigned int GetIndexCount() const;
private:
	unsigned int mIndexCount;
	ID3D11Buffer* mIndexBuffer;
};

