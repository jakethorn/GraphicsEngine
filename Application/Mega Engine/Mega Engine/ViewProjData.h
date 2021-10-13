// Mega

#pragma once

#ifndef VIEW_PROJ_DATA_H
#define VIEW_PROJ_DATA_H

#include "IConstantVariableData.h"

#include <d3d11.h>
#include <xnamath.h>

class Camera;

class ViewProjData : public IConstantVariableData
{
public:
	explicit ViewProjData(Camera *data);

	void * operator()() const;

private:
	mutable XMFLOAT4X4 xmViewProj;
};

#endif