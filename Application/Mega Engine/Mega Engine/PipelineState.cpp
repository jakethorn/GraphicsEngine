#include "PipelineState.h"

#include "Common.h"
#include "DebugConsole.h"
#include "Direct3D.h"
#include "GameMaster.h"
#include "Factory.h"
#include "RenderTarget.h"
#include "IConstantVariableData.h"

PipelineState::PipelineState(	VertexShaderStage			*vss, 
								HullShaderStage				*hss, 
								DomainShaderStage			*dss, 
								GeometryShaderStage			*gss, 
								PixelShaderStage			*pss, 
								ID3D11BlendState			*bs,
								ID3D11DepthStencilState		*ds,
								ID3D11RasterizerState		*rs,
								RenderTarget				*renderTarget, 
								const PIPELINE_STATE_DESC	&desc			) :	mVertexShaderStage	{ vss },
																				mHullShaderStage	{ hss },
																				mDomainShaderStage	{ dss },
																				mGeometryShaderStage{ gss },
																				mPixelShaderStage	{ pss },
																				mRenderTarget		{ renderTarget }, 
																				mDesc				{ desc },
																				mPrimitiveTopology	{ D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST }, 
																				mBlendState			{ bs },
																				mDepthStencilState	{ ds },
																				mRasterizerState	{ rs },
																				mIsActive			{ false },
																				mContext			{ d3d::GetImmediateContext() }
{
	// Nothing to do here
	// This is so ugly -.-
}

PipelineState::~PipelineState()
{
	delete mVertexShaderStage;
	delete mHullShaderStage;
	delete mDomainShaderStage;
	delete mGeometryShaderStage;
	delete mPixelShaderStage;

	ReleaseCOM( mContext );
	ReleaseCOM( mBlendState );
	ReleaseCOM( mDepthStencilState );
	ReleaseCOM( mRasterizerState );

	delete mRenderTarget;
}

void PipelineState::SetShaderResources( SHADER_STAGE shaderStage, UINT startSlot, UINT numResources, ID3D11ShaderResourceView * const *resources )
{
	switch ( shaderStage )
	{
	case VERTEX_STAGE:
		mVertexShaderStage->SetShaderResources( startSlot, numResources, resources );
		break;
	case HULL_STAGE:
		mHullShaderStage->SetShaderResources( startSlot, numResources, resources );
		break;
	case DOMAIN_STAGE:
		mDomainShaderStage->SetShaderResources( startSlot, numResources, resources );
		break;
	case GEOMETRY_STAGE:
		mGeometryShaderStage->SetShaderResources( startSlot, numResources, resources );
		break;
	case PIXEL_STAGE:
		mPixelShaderStage->SetShaderResources( startSlot, numResources, resources );
		break;
	}
}

bool PipelineState::UpdateConstantBuffer( string variableName, IConstantVariableData *pDataFunc )
{
try_again:

	switch ( pDataFunc->shaderStage )
	{
	case VERTEX_STAGE:
		mVertexShaderStage->UpdateConstantVariable( variableName, pDataFunc );
		return true;
	case HULL_STAGE:
		mHullShaderStage->UpdateConstantVariable( variableName, pDataFunc );
		return true;
	case DOMAIN_STAGE:
		mDomainShaderStage->UpdateConstantVariable( variableName, pDataFunc );
		return true;
	case GEOMETRY_STAGE:
		mGeometryShaderStage->UpdateConstantVariable( variableName, pDataFunc );
		return true;
	case PIXEL_STAGE:
		mPixelShaderStage->UpdateConstantVariable( variableName, pDataFunc );
		return true;
	default:

		if		( mVertexShaderStage->HasConstantVariable( variableName ) )		pDataFunc->shaderStage = VERTEX_STAGE;
		else if ( mHullShaderStage->HasConstantVariable( variableName ) )		pDataFunc->shaderStage = HULL_STAGE;
		else if ( mDomainShaderStage->HasConstantVariable( variableName ) )		pDataFunc->shaderStage = DOMAIN_STAGE;
		else if ( mGeometryShaderStage->HasConstantVariable( variableName ) )	pDataFunc->shaderStage = GEOMETRY_STAGE;
		else if ( mPixelShaderStage->HasConstantVariable( variableName ) )		pDataFunc->shaderStage = PIXEL_STAGE;
		else																	return false;

goto try_again;
	}
}

ID3D11ShaderResourceView * const *PipelineState::GetResult(ID3D11ShaderResourceView **result) const
{
	return mRenderTarget->GetResult(result);
}


ID3D11ShaderResourceView* const* PipelineState::GetDepth( ID3D11ShaderResourceView** result ) const
{
	return mRenderTarget->GetDepth( result );
}

void PipelineState::SetPrimaryShaderResource( SHADER_STAGE shaderStage, UINT slot ) const
{
	switch ( shaderStage )
	{
	case VERTEX_STAGE:
		mVertexShaderStage->SetPrimaryShaderResource( slot );
		break;
	case HULL_STAGE:
		mHullShaderStage->SetPrimaryShaderResource( slot );
		break;
	case DOMAIN_STAGE:
		mDomainShaderStage->SetPrimaryShaderResource( slot );
		break;
	case GEOMETRY_STAGE:
		mGeometryShaderStage->SetPrimaryShaderResource( slot );
		break;
	case PIXEL_STAGE:
		mPixelShaderStage->SetPrimaryShaderResource( slot );
		break;
	}
}

void PipelineState::Restore()
{
	// if pipeline state is already active, dont need to restore it
	if (mIsActive)
		return;

	// set this as the active pipeline state
	gm::pps::SetActive(this);

	// clear shader resources
	ID3D11ShaderResourceView *unbind[] {NULL};
	mContext->PSSetShaderResources(0, 1, unbind);	// ATTENTION!

	// set render target
	if (mRenderTarget)
	{
		mRenderTarget->Set();
	}
	else
	{
		static ID3D11RenderTargetView * const backBufferRTV = d3d::GetBackBufferRTV();
		static ID3D11DepthStencilView * const backBufferDSV = d3d::GetBackBufferDSV();
		static D3D11_VIEWPORT &viewport = d3d::GetViewport();

		mContext->OMSetRenderTargets(1, &backBufferRTV, backBufferDSV);
		mContext->RSSetViewports( 1, &viewport );
	}

	/*
		Shader Stage Setters
	*/

	mVertexShaderStage->Restore();
	mHullShaderStage->Restore();
	mDomainShaderStage->Restore();
	mGeometryShaderStage->Restore();
	mPixelShaderStage->Restore();

	/*
		Other Important Setters
	*/

	mContext->IASetPrimitiveTopology(mPrimitiveTopology);				// primitive topology
	mContext->OMSetBlendState(mBlendState, NULL, 0xffffffff);			// blend state
	mContext->OMSetDepthStencilState(mDepthStencilState, 0xffffffff);	// depth stencil state
	mContext->RSSetState( mRasterizerState );							// rasterizer state
}

void PipelineState::Clear()
{
	if (mRenderTarget)
	{
		mRenderTarget->Clear();
	}
	else
	{
		static ID3D11RenderTargetView * const backBufferRTV = d3d::GetBackBufferRTV();
		static ID3D11DepthStencilView * const backBufferDSV = d3d::GetBackBufferDSV();

		mContext->ClearRenderTargetView(backBufferRTV, colour::CLEAR);
		mContext->ClearDepthStencilView(backBufferDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

}