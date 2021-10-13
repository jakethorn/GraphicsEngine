// Mega

#pragma once

#ifndef ROTATE_WORLD_H
#define ROTATE_WORLD_H

#include <d3d11.h>
#include <xnamath.h>

#include "IConstantVariableData.h"

class RotateWorldData : public IConstantVariableData
{
public:
	explicit RotateWorldData( const void *const data );
	
	virtual void *operator()() const;

protected:
	mutable XMFLOAT4X4 mWorld;
};

#endif /* ROTATE_WORLD_H */