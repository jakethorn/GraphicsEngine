#include "CameraPositionData.h"

#include "Camera.h"

CameraPositionData::CameraPositionData(Camera * data) : IConstantVariableData{ data }
{
	mCameraPosition = new float[3];
}

CameraPositionData::~CameraPositionData()
{
	delete[] mCameraPosition;
}

void * CameraPositionData::operator()() const
{
	memcpy(
		mCameraPosition, 
		&(static_cast<Camera *>(mData)->GetPositionF3()), 
		sizeof(float) * 3
	);

	return mCameraPosition;
}