// Mega

#pragma once

#ifndef VERTEX_SHADER_STAGE_H
#define VERTEX_SHADER_STAGE_H

#include <string>

#include "IShaderStage.h"

using std::wstring;

class VertexShaderStage : public IShaderStage<ID3D11VertexShader>
{
public:
	explicit VertexShaderStage( string name, UINT inputLayoutBitset );
	virtual ~VertexShaderStage();

	void Restore();
	void SetPrimaryShaderResource( int slot );

protected:
	ID3D11InputLayout *mInputLayout;
};

#endif /* VERTEX_SHADER_STAGE_H */