// Mega

#pragma once

#ifndef WORLD_VIEW_H
#define WORLD_VIEW_H

#include "IConstantVariableData.h"

#include <d3d11.h>
#include <xnamath.h>

class Camera;

class WorldViewData : public IConstantVariableData
{
public:
	explicit WorldViewData( const IConstantVariableData &worldData, Camera *camera );

	void *operator()() const;

protected:

	const IConstantVariableData *mWorldData;

	mutable XMFLOAT4X4 xmWorld;
	mutable XMFLOAT4X4 xmWorldView;
};

#endif