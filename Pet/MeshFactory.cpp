#include "stdafx.h"
#include "MeshFactory.h"
#include "VertexTypes.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <cmath>

std::string MeshFactory::sGlobalPath;

void MeshFactory::SetGlobalPath(const std::string& Path)
{
	sGlobalPath = Path;
}

StaticMesh* MeshFactory::CreateMesh(ID3D11Device* Device, const std::vector<DirectX::XMFLOAT3>& Positions, const std::vector<DirectX::XMFLOAT3>& Normals, const std::vector<DirectX::XMFLOAT2>& UV0, const std::vector<unsigned int>& Index)
{
	if (Positions.size() != Normals.size() || Normals.size() != UV0.size())
	{
		return nullptr;
	}

	if (Index.size() == 0)
	{
		return nullptr;
	}

	unsigned int VertexCount = Positions.size();
	unsigned int IndexCount = Index.size();

	StandardVertex* Vertices = new StandardVertex[VertexCount];
	unsigned int* Indices = new unsigned int[IndexCount];

	for (unsigned int I = 0; I < VertexCount; I++)
	{
		Vertices[I].Position = Positions[I];
		Vertices[I].Normal = Normals[I];
		Vertices[I].UV0 = UV0[I];
	}

	for (unsigned int I = 0; I < IndexCount; I++)
	{
		Indices[I] = Index[I];
	}

	VertexBuffer* VB = VertexBuffer::Create(Device, Vertices, VertexCount);
	IndexBuffer* IB = IndexBuffer::Create(Device, Indices, IndexCount);

	delete[] Vertices;
	delete[] Indices;

	if (VB == nullptr || IB == nullptr)
	{
		return nullptr;
	}

	return new StaticMesh(VB, IB);
}

StaticMesh* MeshFactory::LoadFBXFromFile(std::string& Error, ID3D11Device* Device, FBXWrapper* FBX, const std::string& Filepath)
{
	FbxScene* Scene = FBX->Import(sGlobalPath + Filepath);

	if (!Scene)
	{
		Error = "Could not load FBX from filepath";
		return nullptr;
	}

	FbxNode* RootNode = Scene->GetRootNode();
	if (!RootNode)
	{
		Error = "Scene is empty";
		return nullptr;
	}

	FbxMesh* FoundMesh = nullptr;

	for (int I = 0; I < RootNode->GetChildCount(); I++)
	{
		FbxNode* ChildNode = RootNode->GetChild(I);

		if (FbxMesh* Mesh = ChildNode->GetMesh())
		{
			FoundMesh = Mesh;
			break;
		}
	}

	if (!FoundMesh)
	{
		Error = "Could not load mesh";
		return nullptr;
	}

	std::vector<DirectX::XMFLOAT3> Positions;
	std::vector<DirectX::XMFLOAT3> Normals;
	std::vector<DirectX::XMFLOAT2> UV0;
	std::vector<unsigned int> Index;

	unsigned long PolyCount = FoundMesh->GetPolygonCount();
	for (unsigned long PolyIndex = 0; PolyIndex < PolyCount; PolyIndex++)
	{
		unsigned long VertexCount = FoundMesh->GetPolygonSize(PolyIndex);

		FbxLayerElementArrayTemplate<FbxVector2>* UVVertices;
		FoundMesh->GetTextureUV(&UVVertices, FbxLayerElement::eTextureDiffuse);

		for (unsigned long VertexIndex = 0; VertexIndex < VertexCount; VertexIndex++)
		{
			VertexIndex = FoundMesh->GetPolygonVertex(PolyIndex, VertexIndex);

			Index.push_back(VertexIndex);

			FbxVector4 FBXVertex = FoundMesh->GetControlPointAt(VertexIndex);

			FbxVector4 FBXNormal;
			FoundMesh->GetPolygonVertexNormal(PolyIndex, VertexIndex, FBXNormal);
			
			Positions.push_back(DirectX::XMFLOAT3(FBXVertex[0], FBXVertex[1], FBXVertex[2]));
			Normals.push_back(DirectX::XMFLOAT3(FBXNormal[0], FBXNormal[1], FBXNormal[2]));

			FbxVector2 UV = UVVertices->GetAt(FoundMesh->GetTextureUVIndex(PolyIndex, VertexIndex));

			UV0.push_back(DirectX::XMFLOAT2(UV[0], UV[1]));
		}
	}

	//for (auto Iter = Index.begin(); Iter != Index.end(); Iter += 3)
	//{
	//	std::swap(*Iter, *(Iter + 2));
	//}
	
	return MeshFactory::CreateMesh(Device, Positions, Normals, UV0, Index);
}

StaticMesh* MeshFactory::LoadOBJFromFile(std::string& Error, ID3D11Device* Device, const std::string& Filepath)
{
	std::vector<DirectX::XMFLOAT3> Positions;
	std::vector<DirectX::XMFLOAT3> Normals;
	std::vector<DirectX::XMFLOAT2> UV0;
	std::vector<unsigned int> Index;

	tinyobj::attrib_t Attrib;
	std::vector<tinyobj::shape_t> Shapes;
	std::vector<tinyobj::material_t> Materials;

	bool Result = tinyobj::LoadObj(&Attrib, &Shapes, &Materials, &Error, (sGlobalPath + Filepath).c_str());

	if (!Result) {
		return nullptr;
	}

	for (size_t s = 0; s < Shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < Shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = Shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = Shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = Attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = Attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = Attrib.vertices[3 * idx.vertex_index + 2];
				tinyobj::real_t nx = Attrib.normals[3 * idx.normal_index + 0];
				tinyobj::real_t ny = Attrib.normals[3 * idx.normal_index + 1];
				tinyobj::real_t nz = Attrib.normals[3 * idx.normal_index + 2];
				tinyobj::real_t tx = Attrib.texcoords[2 * idx.texcoord_index + 0];
				tinyobj::real_t ty = Attrib.texcoords[2 * idx.texcoord_index + 1];

				Positions.push_back(DirectX::XMFLOAT3(vx, vy, vz));
				Normals.push_back(DirectX::XMFLOAT3(nx, ny, nz));
				UV0.push_back(DirectX::XMFLOAT2(tx, ty));

				Index.push_back((3 * idx.vertex_index));
			}
			index_offset += fv;

			Shapes[s].mesh.material_ids[f];
		}
	}

	return MeshFactory::CreateMesh(Device, Positions, Normals, UV0, Index);
}

