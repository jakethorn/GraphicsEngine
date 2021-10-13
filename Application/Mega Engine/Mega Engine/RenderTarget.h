// Mega

#pragma once

#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

#include <d3d11.h>

#include "Colour.h"

class RenderTarget
{
public:
	explicit RenderTarget(UINT numRenderTargets, UINT slices, UINT width, UINT height, const DXGI_FORMAT * const format);
	~RenderTarget();

	void Set() const;
	void Clear(const float * const colour = colour::CLEAR) const;
	ID3D11ShaderResourceView *const *GetResult	( ID3D11ShaderResourceView **result = nullptr ) const;
	ID3D11ShaderResourceView *const *GetDepth	( ID3D11ShaderResourceView **result = nullptr ) const;

private:
	ID3D11DeviceContext *mContext;

	// depth and viewport
	ID3D11DepthStencilView	*mDSV;
	ID3D11ShaderResourceView* mDepthSRV;
	ID3D11Texture2D			*mDSTexture;


	D3D11_VIEWPORT			mViewport;

	ID3D11RenderTargetView *mRTV[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	ID3D11ShaderResourceView *mSRV[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	ID3D11Texture2D *mTexture[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];

	const UINT mNumRenderTargets;
};

#endif