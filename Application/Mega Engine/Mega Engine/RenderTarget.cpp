#include "RenderTarget.h"

#include "Common.h"
#include "DebugConsole.h"
#include "Direct3D.h"
#include "Factory.h"

using console::Print;

RenderTarget::RenderTarget(UINT numRenderTargets, UINT slices, UINT width, UINT height, const DXGI_FORMAT * const format) : mNumRenderTargets(numRenderTargets), mContext(d3d::GetImmediateContext())
{
	// create render target textures and views
	for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
	{
		if (i < mNumRenderTargets)
		{
			factory::CreateRenderTargetTextureB( slices, width, height, format[i], &mTexture[i], &mRTV[i], &mSRV[i] );
		}
		else
		{
			mRTV[i]		= NULL;
			mSRV[i]		= NULL;
			mTexture[i] = NULL;
		}
	}

	// Create depth stencil texture and views
	factory::CreateDepthStencilTextureB( slices, width, height, &mDSTexture, &mDSV, &mDepthSRV );

	// Viewport setup
	mViewport.TopLeftX	= 0.0f;
	mViewport.TopLeftY	= 0.0f;
	mViewport.Width		= static_cast<float>(width);
	mViewport.Height	= static_cast<float>(height);
	mViewport.MinDepth	= 0.0f;
	mViewport.MaxDepth	= 1.0f;
}

RenderTarget::~RenderTarget()
{
	ReleaseCOM(mContext);

	for (int i = 0; i < mNumRenderTargets; i++)
	{
		ReleaseCOM(mRTV[i]);
		ReleaseCOM(mSRV[i]);
		ReleaseCOM(mTexture[i]);
	}

	ReleaseCOM(mDSV);
	ReleaseCOM(mDSTexture);
	ReleaseCOM( mDepthSRV );
}

void RenderTarget::Set() const
{
	// dont forget about the viewport.
	if ( mNumRenderTargets == 0 )
		mContext->OMSetRenderTargets(0, 0, mDSV);
	else
		mContext->OMSetRenderTargets(mNumRenderTargets, mRTV, mDSV);	// create the depth stencil buffer bro.

	mContext->RSSetViewports( 1, &mViewport );
}

void RenderTarget::Clear(const float * const colour) const
{
	for (int i = 0; i < mNumRenderTargets; i++)
	{
		mContext->ClearRenderTargetView(mRTV[i], colour);
	}

	// DEPTH
	mContext->ClearDepthStencilView(mDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

ID3D11ShaderResourceView * const *RenderTarget::GetResult(ID3D11ShaderResourceView **result) const
{
	if (result)
	{
		for (int i = 0; i < mNumRenderTargets; i++)
		{
			result[i] = mSRV[i];
			result[i]->AddRef();
		}
	}

	return mSRV;
}


ID3D11ShaderResourceView* const* RenderTarget::GetDepth( ID3D11ShaderResourceView** result ) const
{
	if ( result )
	{
		(*result) = mDepthSRV;
		(*result)->AddRef();
	}

	return &mDepthSRV;
}