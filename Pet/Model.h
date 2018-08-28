#pragma once

#include "StaticMesh.h"
#include "Material.h"

#include <string>
#include <DirectXMath.h>

class Model
{
public:
	Model(std::string Name);
	~Model();

	void SetMesh(StaticMesh* Mesh);
	void SetMaterial(Material* Material);

	const StaticMesh& GetMesh() const;
	const Material& GetMaterial() const;
	const std::string& GetName() const;
	
	DirectX::XMMATRIX GetModelTransform() const;
private:
	std::string mName;

	StaticMesh* mMesh;
	Material* mMaterial;
};

