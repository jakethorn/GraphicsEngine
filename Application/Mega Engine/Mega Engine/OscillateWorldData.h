// Mega

#pragma once

#ifndef OSCILLATE_WORLD_H
#define OSCILLATE_WORLD_H

#include <d3d11.h>
#include <xnamath.h>

#include "IConstantVariableData.h"

class OscillateWorldData : public IConstantVariableData
{
public:
	explicit OscillateWorldData( const void *const data );
	
	virtual void *operator()() const;

protected:
	mutable XMFLOAT4X4 mWorld;
};

#endif /* OSCILLATE_WORLD_H */