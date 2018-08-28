#include "stdafx.h"
#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
{
}


VertexBuffer::~VertexBuffer()
{
	if (mVertexBuffer)
	{
		mVertexBuffer->Release();
	}
}

ID3D11Buffer* VertexBuffer::GetInternalBuffer() const
{
	return mVertexBuffer;
}

unsigned int VertexBuffer::GetVertexSize() const
{
	return mVertexSize;
}
