#pragma once

#include "Camera.h"

#include <DirectXMath.h>

struct SceneDescription
{
	SceneDescription(const Camera* Cam)
		: mCamera(Cam)
	{

	}

	DirectX::XMMATRIX mWorldMatrix;

	const Camera* mCamera;
};