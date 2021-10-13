// Mega

#pragma once

#ifndef PIXEL_SHADER_STAGE_H
#define PIXEL_SHADER_STAGE_H

#include <string>

#include "IShaderStage.h"

using std::wstring;

class PixelShaderStage : public IShaderStage<ID3D11PixelShader>
{
public:
	explicit PixelShaderStage( string name );

	void Restore();
	void SetPrimaryShaderResource( int slot );
};

#endif /* PIXEL_SHADER_STAGE_H */