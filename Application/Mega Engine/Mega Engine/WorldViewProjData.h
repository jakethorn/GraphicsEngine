// Mega

#pragma once

#ifndef WORLD_VIEW_PROJ_H
#define WORLD_VIEW_PROJ_H

#include "IConstantVariableData.h"

#include <d3d11.h>
#include <xnamath.h>

class Camera;

class WorldViewProjData : public IConstantVariableData
{
public:
	explicit WorldViewProjData( const IConstantVariableData &worldData, Camera *camera );

	void *operator()() const;

protected:

	const IConstantVariableData *mWorldData;

	mutable XMFLOAT4X4 xmWorld;
	mutable XMFLOAT4X4 xmWorldViewProj;
};

#endif