#include "Camera.h"

CAMERA_DESC::CAMERA_DESC(string _name) : name{ _name }
{

}

Camera::Camera(string name) :	mPosition(0.0f, 0.0f, 0.0f),
								mRight(1.0f, 0.0f, 0.0f),
								mUp(0.0f, 1.0f, 0.0f),
								mLook(0.0f, 0.0f, 1.0f),
								mDesc{ name }
{
	SetFrustum(0.25f * XM_PI, 1.0f, 1.0f, 10.0f);
}

Camera::Camera(const CAMERA_DESC & desc) : Camera{ desc.name }
{

}

void Camera::SetFrustum(float fov, float aspectRatio, float nearZ, float farZ) 
{

	XMMATRIX P = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);
	XMStoreFloat4x4(&mProj, P);
}

void Camera::SetOrthoFrustum( float l, float r, float b, float t, float n, float f )
{
	XMMATRIX P = XMMatrixOrthographicOffCenterLH( l, r, b, t, n, f );
	XMStoreFloat4x4( &mProj, P );
}

void Camera::LookAtV(FXMVECTOR target)
{
	FXMVECTOR P = XMLoadFloat3(&mPosition);
	FXMVECTOR Y = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	FXMVECTOR L = XMVector3Normalize(XMVectorSubtract(target, P));
	FXMVECTOR R = XMVector3Normalize(XMVector3Cross(Y, L));
	FXMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat3(&mLook, L);
	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
}

void Camera::LookAtF3(const XMFLOAT3& target)
{
	XMVECTOR T = XMLoadFloat3(&target);
	LookAtV(T);
}

void Camera::TranslateX(float vel) 
{

	// mPosition += displacement * mRight
	XMVECTOR s = XMVectorReplicate(vel);
	XMVECTOR r = XMLoadFloat3(&mRight);
	XMVECTOR p = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, r, p));
}

void Camera::TranslateWorldY(float vel) 
{

	// mPosition += displacement * mUp
	XMVECTOR s = XMVectorReplicate(vel);
	XMVECTOR u = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR p = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, u, p));
}

void Camera::TranslateZ(float vel) 
{

	// mPosition += displacement * mLook
	XMVECTOR s = XMVectorReplicate(vel);
	XMVECTOR l = XMLoadFloat3(&mLook);
	XMVECTOR p = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, l, p));
}

void Camera::RotateX(float vel) 
{

	// rotate up and look vector about the right vector

	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&mRight), vel);

	XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), R));
}

void Camera::RotateY(float vel) 
{

	// rotate the basis vectors about the world y-axis

	XMMATRIX R = XMMatrixRotationY(vel);

	XMStoreFloat3(&mRight, XMVector3TransformNormal(XMLoadFloat3(&mRight), R));
	XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), R));
}

void Camera::Update() 
{

	XMVECTOR R = XMLoadFloat3(&mRight);
	XMVECTOR U = XMLoadFloat3(&mUp);
	XMVECTOR L = XMLoadFloat3(&mLook);
	XMVECTOR P = XMLoadFloat3(&mPosition);

	// keep cameras axes orthogonal to each other and of unit length
	L = XMVector3Normalize(L);
	U = XMVector3Normalize(XMVector3Cross(L, R));

	// U, L already orthonormal, so no need to normalize cross product
	R = XMVector3Cross(U, L);

	// fill in the view matrix
	float x = -XMVectorGetX(XMVector3Dot(P, R));
	float y = -XMVectorGetX(XMVector3Dot(P, U));
	float z = -XMVectorGetX(XMVector3Dot(P, L));

	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
	XMStoreFloat3(&mLook, L);

	mView(0, 0) = mRight.x;
	mView(1, 0) = mRight.y;
	mView(2, 0) = mRight.z;
	mView(3, 0) = x;

	mView(0, 1) = mUp.x;
	mView(1, 1) = mUp.y;
	mView(2, 1) = mUp.z;
	mView(3, 1) = y;

	mView(0, 2) = mLook.x;
	mView(1, 2) = mLook.y;
	mView(2, 2) = mLook.z;
	mView(3, 2) = z;

	mView(0, 3) = 0.0f;
	mView(1, 3) = 0.0f;
	mView(2, 3) = 0.0f;
	mView(3, 3) = 1.0f;
}