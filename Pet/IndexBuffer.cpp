#include "stdafx.h"
#include "IndexBuffer.h"


IndexBuffer::IndexBuffer()
{
}


IndexBuffer::~IndexBuffer()
{
	if (mIndexBuffer)
	{
		mIndexBuffer->Release();
	}
}

IndexBuffer* IndexBuffer::Create(ID3D11Device * Device, unsigned int* Indices, size_t Count)
{
	IndexBuffer* Buffer = new IndexBuffer;

	D3D11_BUFFER_DESC IndexBufferDesc;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.ByteWidth = sizeof(unsigned int) * Count;
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;
	IndexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA IndexData;
	IndexData.pSysMem = Indices;
	IndexData.SysMemPitch = 0;
	IndexData.SysMemSlicePitch = 0;

	if (FAILED(Device->CreateBuffer(&IndexBufferDesc, &IndexData, &Buffer->mIndexBuffer)))
	{
		delete Buffer;
		return nullptr;
	}

	Buffer->mIndexCount = Count;

	return Buffer;
}


ID3D11Buffer* IndexBuffer::GetInternalBuffer() const
{
	return mIndexBuffer;
}

unsigned int IndexBuffer::GetIndexCount() const
{
	return mIndexCount;
}
