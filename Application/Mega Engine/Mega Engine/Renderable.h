// Mega

#pragma once

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <d3d11.h>
#include <string>
#include <xnamath.h>

#include "Camera.h"
#include "ConstantBufferData.h"
#include "IConstantVariableData.h"
#include "PipelineState.h"

using std::string;

struct RENDERABLE_DESC
{
	string	pipelineState	= "";	
	string	camera			= "";
	string	shape			= "";
	int		layer			= 0;

	bool	shadowEnabled	= false;
	string	shadowPPS		= "";
	string	shadowCam		= "";
	float	shadowBias		= 0.0f;

	bool	reflectEnabled	= false;
	string	reflectPPS		= "";
	string	reflectCam		= "";

	string	reflectorCam	= "";

	RENDERABLE_DESC() = default;
	RENDERABLE_DESC( const RENDERABLE_DESC & ) = default;
};

class Renderable
{
public:
	explicit Renderable( PipelineState * pps, ConstantBufferData cb, const RENDERABLE_DESC & desc );

	void SetPipelineState( PipelineState *newPps );
	void SetCamera( Camera * const newCamera );
	void SetShadowCamera( Camera * const newCamera );
	void SetReflectorCamera( Camera * const newCamera );
	void SetPrimaryPSShaderResourceSlot( int slot )	{ mPSShaderResourceSlot = slot; }
	void SetSRV( ID3D11ShaderResourceView* srv ) { mSRV = srv; }

	void Draw();

	RENDERABLE_DESC &GetDesc() const { return mDesc; }

protected:
	void UpdateConstantBufferData( string variableName, void *const pData );

	const Camera		*mCamera;
	PipelineState		*mPps;
	ID3D11DeviceContext	*mContext;

	ConstantBufferData mConstantBufferData;

	int mPSShaderResourceSlot;
	ID3D11ShaderResourceView *mSRV;

	mutable RENDERABLE_DESC mDesc;
};

#endif