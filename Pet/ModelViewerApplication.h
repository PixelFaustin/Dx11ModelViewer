#pragma once

#include "Application.h"
#include "Color.h"
#include "StandardMeshShader.h"
#include "StaticMesh.h"
#include "Texture2D.h"
#include "Camera.h"

class ModelViewerApplication : public Application
{
public:
	ModelViewerApplication(Canvas* _Canvas);
	~ModelViewerApplication();

	virtual bool Initialize() override;

	virtual void Update(float DeltaTime) override;
	virtual void Render(Renderer* _Renderer) override;

	virtual bool OnRun(float DeltaTime) override;
private:
	Model* CreateTriangleModel() const;
	StaticMesh* CreateTriangleMesh() const;
private:
	Camera* mCamera;
	Model* mTriangleModel;
	StaticMesh* mLoadedMesh;
};

