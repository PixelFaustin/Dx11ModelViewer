#include "stdafx.h"
#include "Model.h"


Model::Model(std::string Name)
	: mName(Name)
{
}


Model::~Model()
{
	if (mMesh)
	{
		delete mMesh;
	}

	if (mMaterial)
	{
		delete mMaterial;
	}
}

void Model::SetMesh(StaticMesh * Mesh)
{
	mMesh = Mesh;
}

void Model::SetMaterial(Material * Material)
{
	mMaterial = Material;
}

const StaticMesh& Model::GetMesh() const
{
	return *mMesh;
}

const Material & Model::GetMaterial() const
{
	return *mMaterial;
}

const std::string& Model::GetName() const
{
	return mName;
}

DirectX::XMMATRIX Model::GetModelTransform() const
{
	return DirectX::XMMatrixIdentity();
}
