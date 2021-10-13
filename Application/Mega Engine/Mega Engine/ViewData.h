// Mega

#pragma once

#ifndef VIEW_DATA_H
#define VIEW_DATA_H

#include "IConstantVariableData.h"

#include <d3d11.h>
#include <xnamath.h>

class Camera;

class ViewData : public IConstantVariableData
{
public:
	explicit ViewData(Camera *data);

	void * operator()() const;

private:
	mutable XMFLOAT4X4 xmView;
};

#endif