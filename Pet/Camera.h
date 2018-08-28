#pragma once

#include <DirectXMath.h>

class Camera
{
public:
	Camera(DirectX::XMFLOAT3 Position, DirectX::XMFLOAT3 Forward, DirectX::XMFLOAT3 Up);
	~Camera();

	void InitializeProjection(float FOV, float Aspect, float Near, float Far);

	void Update(float DeltaTime);

	DirectX::XMMATRIX GetViewMatrix() const;
	DirectX::XMMATRIX GetProjectionMatrix() const;
private:
	void UpdateViewMatrix();
private:
	float mFOV;
	float mAspect;
	float mNear;
	float mFar;

	DirectX::XMFLOAT3 mForward;
	DirectX::XMFLOAT3 mUp;

	DirectX::XMFLOAT3 mWorldUp;

	DirectX::XMFLOAT3 mPosition;

	DirectX::XMMATRIX mViewMatrix;
	DirectX::XMMATRIX mProjectionMatrix;
};

