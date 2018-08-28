#include "stdafx.h"
#include "StaticMesh.h"

const PrimitiveTopology Default = TriangleList;

StaticMesh::StaticMesh(VertexBuffer* VB, IndexBuffer* IB)
	: mVertexBuffer(VB), mIndexBuffer(IB)
{
	mTopology = Default;
}

StaticMesh::~StaticMesh()
{
	if (mVertexBuffer)
	{
		delete mVertexBuffer;
	}

	if (mIndexBuffer)
	{
		delete mIndexBuffer;
	}
}

PrimitiveTopology StaticMesh::GetTopology() const
{
	return mTopology;
}

const VertexBuffer* StaticMesh::GetVertexBuffer() const
{
	return mVertexBuffer;
}

const IndexBuffer* StaticMesh::GetIndexBuffer() const
{
	return mIndexBuffer;
}

unsigned int StaticMesh::GetIndexCount() const
{
	return mIndexBuffer->GetIndexCount();
}

unsigned int StaticMesh::GetVertexSize() const
{
	return mVertexBuffer->GetVertexSize();
}
