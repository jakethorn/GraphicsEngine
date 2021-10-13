// Mega

#pragma once

#ifndef PIPELINE_STATE_H
#define PIPELINE_STATE_H

#include <d3d11.h>
#include <d3d11shader.h>

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "IShaderStage.h"
#include "VertexShaderStage.h"
#include "HullShaderStage.h"
#include "DomainShaderStage.h"
#include "GeometryShaderStage.h"
#include "PixelShaderStage.h"

// forward declarations

class RENDER_TARGET_DESC;
class IConstantVariableData;
class RenderTarget;

using std::map;
using std::pair;
using std::string;
using std::vector;
using std::wstring;

/*	NEW DESC STUFF */

struct PIPELINE_STATE_DESC
{
	string	name		= "";

	string	attachTo	= "";
	int		numViews	= 0;
	bool	attachDepth	= false;
};

/*	NEW DESC STUFF */

using ConstantBuffer = std::map<std::string, ConstantVariable>; 

class PipelineState
{
public:
	explicit PipelineState(	VertexShaderStage			*vss, 
							HullShaderStage				*hss, 
							DomainShaderStage			*dss, 
							GeometryShaderStage			*gss, 
							PixelShaderStage			*pss, 
							ID3D11BlendState			*bs,
							ID3D11DepthStencilState		*ds,
							ID3D11RasterizerState		*rs,
							RenderTarget				*renderTarget, 
							const PIPELINE_STATE_DESC	&desc );
	
	~PipelineState();

	void SetShaderResources( SHADER_STAGE shaderStage, UINT startSlot, UINT numResources, ID3D11ShaderResourceView * const *resources );
	bool UpdateConstantBuffer( string variableName, IConstantVariableData *pDataFunc );

	// Setters

	void SetPrimaryShaderResource( SHADER_STAGE shaderStage, UINT slot ) const;
	void SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY topology ) { mPrimitiveTopology = topology; }

	// Getters
	
	ID3D11ShaderResourceView *const *GetResult	( ID3D11ShaderResourceView **result = nullptr ) const;
	ID3D11ShaderResourceView *const *GetDepth	( ID3D11ShaderResourceView** result = nullptr ) const;

	const PIPELINE_STATE_DESC		&GetDesc() const { return mDesc; }

	/*
		Renderer Functions
	*/

	void Restore();													// Restore the pipeline state
	void Clear();													// Clear render targets
	void SetIsActive( bool isActive ) { mIsActive = isActive; }		// Set as the active pipeline state

private:

	/*
		Shader Stages
	*/

	VertexShaderStage	*mVertexShaderStage;
	HullShaderStage *mHullShaderStage;
	DomainShaderStage *mDomainShaderStage;
	GeometryShaderStage *mGeometryShaderStage;
	PixelShaderStage	*mPixelShaderStage;

	/*
		Other Important Variables
	*/
	
	ID3D11DeviceContext			*mContext;				// Cached immediate context

	bool						mIsActive;				// Active variable
	PIPELINE_STATE_DESC			mDesc;					// Pipeline States Description
	
	D3D11_PRIMITIVE_TOPOLOGY	mPrimitiveTopology;		// Primitive topology
	ID3D11BlendState			*mBlendState;			// Blend state
	ID3D11DepthStencilState		*mDepthStencilState;	// Depth stencil state
	ID3D11RasterizerState		*mRasterizerState;		// Rasterizer state
	
	RenderTarget				*mRenderTarget;			// Render target
};

#endif