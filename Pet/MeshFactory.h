#pragma once

#include "StaticMesh.h"
#include "FBXWrapper.h"

#include <vector>
#include <string>

#include <d3d11.h>
#include <DirectXMath.h>

class MeshFactory
{
public:
	static void SetGlobalPath(const std::string& Path);

	static StaticMesh* CreateMesh(
		ID3D11Device* Device,
		const std::vector<DirectX::XMFLOAT3>& Positions,
		const std::vector<DirectX::XMFLOAT3>& Normals,
		const std::vector<DirectX::XMFLOAT2>& UV0,
		const std::vector<unsigned int>& Index);

	static StaticMesh* LoadFBXFromFile(std::string& Error, ID3D11Device* Device, FBXWrapper* FBX, const std::string& Filepath);
	static StaticMesh* LoadOBJFromFile(std::string& Error, ID3D11Device* Device, const std::string& Filepath);
private:
	static std::string sGlobalPath;
};

