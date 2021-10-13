// Mega

#pragma once

#ifndef DIRECT3D_H
#define DIRECT3D_H

#include <d3d11.h>

namespace d3d
{
	void SetDevice				(ID3D11Device			*device);
	void SetImmediateContext	(ID3D11DeviceContext	*context);
	void SetSwapChain			(IDXGISwapChain			*swapChain);
	void SetBackBufferRTV		(ID3D11RenderTargetView *RTV,		bool onResize = false);
	void SetBackBufferDSV		(ID3D11DepthStencilView *DSV,		bool onResize = false);
	void SetDepthStencilBuffer	(ID3D11Texture2D		*DSB,		bool onResize = false);
	void SetViewport			(D3D11_VIEWPORT			viewport,	bool onResize = false);

	ID3D11Device			* const GetDevice				(ID3D11Device			**device	= nullptr);
	ID3D11DeviceContext		* const GetImmediateContext		(ID3D11DeviceContext	**context	= nullptr);
	IDXGISwapChain			* const GetSwapChain			(IDXGISwapChain			**swapChain = nullptr);
	ID3D11RenderTargetView	* const GetBackBufferRTV		(ID3D11RenderTargetView	**RTV		= nullptr);
	ID3D11DepthStencilView	* const GetBackBufferDSV		(ID3D11DepthStencilView	**DSV		= nullptr);
	ID3D11Texture2D			* const GetDepthStencilBuffer	(ID3D11Texture2D		**DSB		= nullptr);
	D3D11_VIEWPORT			&		GetViewport();

	void ReleaseBackBufferRTV();
	void ReleaseBackBufferDSV();
	void ReleaseBackBufferDSB();
	void ReleaseAll();

	// Msaa.
	const bool gEnableMsaa = false;
	const UINT gSampleCount = 4;

	void Init(HWND hWnd, UINT width, UINT height);
	void Resize(UINT width, UINT height);
	void Unin();
}

#endif