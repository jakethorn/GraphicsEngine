// Mega

#pragma once

#ifndef CONSTANT_VARIABLE_DATA_FACTORY_H
#define CONSTANT_VARIABLE_DATA_FACTORY_H

#include "IConstantVariableData.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class ConstantVariableDataFactory
{
public:
	template<typename T>
	static IConstantVariableData *Create( vector<T> data )
	{
		return ( data.size() > 0 ) ? new IConstantVariableData{ &data[0], sizeof( T ) * data.size() } : new IConstantVariableData{ nullptr, 0 };
	}

	template<typename T>
	static IConstantVariableData *Create( T data )
	{
		return new IConstantVariableData{ &data, sizeof( T ) };
	}

	static IConstantVariableData *CreateWorldMatrix( string movementType, const float *const position, const float *const scale, const float *const rotation );
	static IConstantVariableData *CreateWorldInverseTransposeMatrix();
	static IConstantVariableData *CreateWorldViewMatrix();
	static IConstantVariableData *CreateWorldViewProjMatrix( bool shouldFollowPlayer );
	static IConstantVariableData *CreateViewMatrix();
	static IConstantVariableData *CreateViewProjMatrix();
	static IConstantVariableData *CreateShadowTextureMatrix();
	
	static IConstantVariableData *CreateCameraPosition();

private:
	static IConstantVariableData *mCachedWorldMatrix;
};

#endif /* CONSTANT_VARIABLE_DATA_FACTORY_H */