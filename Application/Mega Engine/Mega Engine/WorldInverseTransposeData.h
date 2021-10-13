// Mega

#pragma once

#ifndef WORLD_INVERSE_TRANSPOSE_DATA_H
#define WORLD_INVERSE_TRANSPOSE_DATA_H

#include "IConstantVariableData.h"

#include <d3d11.h>
#include <xnamath.h>

class Camera;

class WorldInverseTransposeData : public IConstantVariableData
{
public:
	explicit WorldInverseTransposeData( const IConstantVariableData &worldData );

	void *operator()() const;

protected:

	const IConstantVariableData *mWorldData;

	mutable XMFLOAT4X4 xmWorld;
};

#endif /* WORLD_INVERSE_TRANSPOSE_DATA_H */