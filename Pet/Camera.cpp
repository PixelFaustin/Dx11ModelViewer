#include "stdafx.h"
#include "Camera.h"

using namespace DirectX;

Camera::Camera(DirectX::XMFLOAT3 Position, DirectX::XMFLOAT3 Forward, DirectX::XMFLOAT3 Up)
{
	mUp = Up;
	mForward = Forward;
	mPosition = Position;
	mWorldUp = DirectX::XMFLOAT3(0.f, 1.f, 0.f);

	UpdateViewMatrix();
}


Camera::~Camera()
{
}

void Camera::InitializeProjection(float FOV, float Aspect, float Near, float Far)
{
	mFOV = DirectX::XMConvertToRadians(FOV);
	mAspect = Aspect;
	mNear = Near;
	mFar = Far;

	mProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(mFOV, mAspect, mNear, mFar);
}

void Camera::Update(float DeltaTime)
{
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	DirectX::XMVECTOR Position = DirectX::XMLoadFloat3(&mPosition);
	DirectX::XMVECTOR _Forward = DirectX::XMLoadFloat3(&mForward);
	DirectX::XMVECTOR Focus = Position + _Forward;
	XMVECTOR Up = XMLoadFloat3(&mUp);
	mViewMatrix = DirectX::XMMatrixLookAtLH(Position, Focus, Up);
}

DirectX::XMMATRIX Camera::GetViewMatrix() const
{
	return mViewMatrix;
}

DirectX::XMMATRIX Camera::GetProjectionMatrix() const
{
	return mProjectionMatrix;
}
