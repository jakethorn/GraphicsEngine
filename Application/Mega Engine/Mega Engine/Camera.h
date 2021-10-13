#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx11.h>
#include <string>
#include <xnamath.h>

using std::string;

struct CAMERA_DESC
{
	explicit CAMERA_DESC(string _name);

	string name;
};

class Camera {

public:

	explicit Camera(string name);
	explicit Camera(const CAMERA_DESC & desc);
	
	// get/set camera position
	XMVECTOR GetPositionV	() const					{ return XMLoadFloat3(&mPosition); }
	XMFLOAT3 GetPositionF3	() const					{ return mPosition; }
	void SetPositionV		(FXMVECTOR position)		{ XMStoreFloat3(&mPosition, position); }
	void SetPositionF3		(const XMFLOAT3& position)	{ mPosition = position; }

	// get camera direction vectors
	XMVECTOR GetRightV	() const { return XMLoadFloat3(&mRight); }
	XMVECTOR GetUpV		() const { return XMLoadFloat3(&mUp); }
	XMVECTOR GetLookV	() const { return XMLoadFloat3(&mLook); }
	XMFLOAT3 GetRightF3	() const { return mRight; }
	XMFLOAT3 GetUpF3	() const { return mUp; }
	XMFLOAT3 GetLookF3	() const { return mLook; }

	void SetFrustum(float fov, float aspectRatio, float nearZ, float farZ);
	void SetOrthoFrustum( float l, float r, float b, float t, float n, float f );

	// set view space
	void LookAtV(FXMVECTOR target);
	void LookAtF3(const XMFLOAT3& target);

	// get camera matrices
	XMMATRIX GetView	() const { return XMLoadFloat4x4(&mView); }
	XMMATRIX GetProj	() const { return XMLoadFloat4x4(&mProj); }
	XMMATRIX GetViewProj() const { return GetView() * GetProj(); }

	// walk
	void TranslateX(float vel);
	void TranslateWorldY(float vel);
	void TranslateZ(float vel);

	// rotate
	void RotateX(float vel);
	void RotateY(float vel);

	// update view matrix 
	void Update();

	const CAMERA_DESC & GetDesc() const { return mDesc; }

private:
	const CAMERA_DESC mDesc;

	// camera position and direction vectors
	XMFLOAT3 mPosition;
	XMFLOAT3 mRight;
	XMFLOAT3 mUp;
	XMFLOAT3 mLook;

	// cached camera matrices
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;
};

#endif	// #ifndef CAMERA_H