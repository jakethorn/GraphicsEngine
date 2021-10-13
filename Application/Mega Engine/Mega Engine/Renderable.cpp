#include "Renderable.h"

#include "Direct3D.h"
#include "VertexBuffer.h"

Renderable::Renderable(PipelineState * pps, ConstantBufferData cb, const RENDERABLE_DESC &desc) :	mPps{ pps }, 
																									mConstantBufferData{ cb }, 
																									mContext{ d3d::GetImmediateContext() },
																									mDesc{ desc },
																									mSRV{ nullptr }
{

}

void Renderable::SetPipelineState(PipelineState *pps)
{
	mPps = pps;
}

void Renderable::SetCamera( Camera *const camera )
{
	UpdateConstantBufferData( "gWorldViewProj", camera );
	UpdateConstantBufferData( "gWorldView",		camera );
	UpdateConstantBufferData( "gViewProj",		camera );
	UpdateConstantBufferData( "gCameraPos",		camera );
}

void Renderable::SetShadowCamera( Camera *const camera )
{
	UpdateConstantBufferData( "gShadowTex", camera );
}

void Renderable::SetReflectorCamera( Camera *const camera )
{
	UpdateConstantBufferData( "gParaboloidBasis", camera );
}

void Renderable::Draw()
{
	// restore pipeline and set the wanted shader resource slot
	mPps->Restore();
	mPps->SetPrimaryShaderResource(PIXEL_STAGE, mPSShaderResourceSlot);

	// if the renderable has a texture to set, set it
	if ( mSRV )
		mPps->SetShaderResources( PIXEL_STAGE, 0, 1, &mSRV );

	// update shader constant buffers
	for ( auto i = mConstantBufferData.begin(); i != mConstantBufferData.end(); /* no increment */ )
	{
		// attempt to update constant buffer variable
		bool succeeded = mPps->UpdateConstantBuffer( i->first, i->second );

		// if attempt failed, erase variable
		if ( !succeeded )
			mConstantBufferData.erase( i++ );
		else
			++i;
	}

	// draw renderable
	vb::Draw(mDesc.shape);
}

/*
	Helper Functions
*/

void Renderable::UpdateConstantBufferData( string variableName, void *const pData )
{
	auto a = mConstantBufferData.find( variableName );
	if (a != mConstantBufferData.end())
		(*a->second)( pData );
}
