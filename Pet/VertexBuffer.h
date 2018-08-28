#pragma once

#include <d3d11.h>

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	template<typename VertexType>
	static VertexBuffer* Create(ID3D11Device* Device, VertexType* Vertices, size_t Count)
	{
		VertexBuffer* Buffer = new VertexBuffer;

		D3D11_BUFFER_DESC VertexBufferDesc;
		VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		VertexBufferDesc.ByteWidth = sizeof(VertexType) * Count;
		VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		VertexBufferDesc.CPUAccessFlags = 0;
		VertexBufferDesc.MiscFlags = 0;
		VertexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA VertexData;
		VertexData.pSysMem = Vertices;
		VertexData.SysMemPitch = 0;
		VertexData.SysMemSlicePitch = 0;

		if (FAILED(Device->CreateBuffer(&VertexBufferDesc, &VertexData, &Buffer->mVertexBuffer)))
		{
			delete Buffer;
			return nullptr;
		}

		Buffer->mVertexSize = sizeof(VertexType);

		return Buffer;
	}

	ID3D11Buffer* GetInternalBuffer() const;
	unsigned int GetVertexSize() const;
private:
	ID3D11Buffer* mVertexBuffer;
	unsigned int mVertexSize;
};

