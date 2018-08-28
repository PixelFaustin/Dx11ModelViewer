#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "PrimitiveTopology.h"

class StaticMesh
{
public:
	StaticMesh(VertexBuffer* VB, IndexBuffer* IB);
	~StaticMesh();

	PrimitiveTopology GetTopology() const;
	const VertexBuffer* GetVertexBuffer() const;
	const IndexBuffer* GetIndexBuffer() const;

	unsigned int GetIndexCount() const;

	unsigned int GetVertexSize() const;
private:
	PrimitiveTopology mTopology;

	VertexBuffer* mVertexBuffer;
	IndexBuffer* mIndexBuffer;
};

