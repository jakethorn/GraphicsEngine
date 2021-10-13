// Mega

#pragma once

#ifndef CAMERA_POSITION_DATA_H
#define CAMERA_POSITION_DATA_H

#include "IConstantVariableData.h"

class Camera;

class CameraPositionData : public IConstantVariableData
{
public:
	explicit CameraPositionData(Camera * data);
	~CameraPositionData();

	void * operator()() const;

private:
	float * mCameraPosition;
};

#endif