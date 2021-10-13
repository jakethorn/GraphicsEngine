// Mega

#pragma once

#ifndef I_CONSTANT_BUFFER_DATA_H
#define I_CONSTANT_BUFFER_DATA_H

#include "ShaderStages.h"

class IConstantVariableData
{
public:
	explicit IConstantVariableData( void *const data );
	explicit IConstantVariableData( const void *const data, size_t size );

	virtual ~IConstantVariableData();

	virtual void *operator()() const;
	virtual void operator()( void *const data );
	virtual void operator()( const void *const data, size_t size );

	SHADER_STAGE shaderStage = UNKNOWN_STAGE;

protected:
	void *mData;
	bool mHasOwnership = false;
};

#endif