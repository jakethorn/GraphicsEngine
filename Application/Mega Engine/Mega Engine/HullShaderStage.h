// Mega

#pragma once

#ifndef HULL_SHADER_STAGE_H
#define HULL_SHADER_STAGE_H

#include <string>

#include "IShaderStage.h"

using std::wstring;

class HullShaderStage : public IShaderStage<ID3D11HullShader>
{
public:
	explicit HullShaderStage( string name );

	void Restore();
	void SetPrimaryShaderResource( int slot );
};

#endif /* HULL_SHADER_STAGE_H */