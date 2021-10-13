// Mega

#pragma once

#ifndef GEOMETRY_SHADER_STAGE_H
#define GEOMETRY_SHADER_STAGE_H

#include <string>

#include "IShaderStage.h"

using std::wstring;

class GeometryShaderStage : public IShaderStage<ID3D11GeometryShader>
{
public:
	explicit GeometryShaderStage( string name );

	void Restore();
	void SetPrimaryShaderResource( int slot );
};

#endif /* GEOMETRY_SHADER_STAGE_H */