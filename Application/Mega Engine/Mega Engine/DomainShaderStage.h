// Mega

#pragma once

#ifndef DOMAIN_SHADER_STAGE_H
#define DOMAIN_SHADER_STAGE_H

#include <string>

#include "IShaderStage.h"

using std::wstring;

class DomainShaderStage : public IShaderStage<ID3D11DomainShader>
{
public:
	explicit DomainShaderStage( string name );

	void Restore();
	void SetPrimaryShaderResource( int slot );
};

#endif /* DOMAIN_SHADER_STAGE_H */