#pragma once

#include <string>

#include <fbxsdk.h>

class FBXWrapper
{
public:
	FBXWrapper();
	~FBXWrapper();

	void Initialize();

	FbxScene* Import(const std::string& FullPath);
private:
	FbxManager* mFBXManager;
	FbxIOSettings* mIOSettings;
	
};

