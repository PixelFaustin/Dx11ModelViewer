#include "stdafx.h"
#include "FBXWrapper.h"


FBXWrapper::FBXWrapper()
{
}


FBXWrapper::~FBXWrapper()
{
	if (mFBXManager)
	{
		mFBXManager->Destroy();
	}
}

void FBXWrapper::Initialize()
{
	mFBXManager = FbxManager::Create();
	mIOSettings = FbxIOSettings::Create(mFBXManager, IOSROOT);

	mFBXManager->SetIOSettings(mIOSettings);
}

FbxScene* FBXWrapper::Import(const std::string& FullPath)
{
	FbxImporter* Importer = FbxImporter::Create(mFBXManager, "");
	
	if (!Importer->Initialize(FullPath.c_str(), -1, mFBXManager->GetIOSettings()))
	{
		Importer->Destroy();
		return nullptr;
	}

	FbxScene* Scene = FbxScene::Create(mFBXManager, "MyScene");
		
	Importer->Import(Scene);

	Importer->Destroy();

	return Scene;
}

