// Mega

#pragma once

#ifndef FACTORY_H
#define FACTORY_H

#include <windows.h>

#include <d3d11.h>
#include <d3dX11.h>

#include <D3D11Shader.h>

namespace factory
{
	// SHADERS

	ID3D11VertexShader		*CreateVertexShaderFromFile		( LPCWSTR file, LPCSTR funcName, ID3D11ShaderReflection **reflection = nullptr );
	ID3D11HullShader		*CreateHullShaderFromFile		( LPCWSTR file, LPCSTR funcName, ID3D11ShaderReflection **reflection = nullptr );
	ID3D11DomainShader		*CreateDomainShaderFromFile		( LPCWSTR file, LPCSTR funcName, ID3D11ShaderReflection **reflection = nullptr );
	ID3D11GeometryShader	*CreateGeometryShaderFromFile	( LPCWSTR file, LPCSTR funcName, ID3D11ShaderReflection **reflection = nullptr );
	ID3D11PixelShader		*CreatePixelShaderFromFile		( LPCWSTR file, LPCSTR funcName, ID3D11ShaderReflection **reflection = nullptr );

	void CreateVertexShaderAndInputLayoutFromFile	( LPCWSTR file, LPCSTR funcName, D3D11_INPUT_ELEMENT_DESC *inputElementDescs, UINT numElements, ID3D11VertexShader **vertexShader, ID3D11InputLayout **inputLayout, ID3D11ShaderReflection **reflection = nullptr );

	// BUFFERS

	ID3D11Buffer *CreateVertexBuffer	( bool streamOut, bool cpuAccess,	const float * const data, UINT byteWidth );
	ID3D11Buffer *CreateIndexBuffer		( bool cpuAccess,					const UINT	* const data, UINT byteWidth );

	ID3D11Buffer *CreateStagingBuffer	( UINT byteWidth,											ID3D11Buffer **buffer = nullptr );
	ID3D11Buffer *CreateConstantBuffer	( bool updatable, const float * const data, UINT byteWidth, ID3D11Buffer **buffer = nullptr );
	
	// TEXTURES

	ID3D11Texture2D *CreateRenderTargetTexture2D( UINT width, UINT height, DXGI_FORMAT format, bool cpuAccess, ID3D11Texture2D **texture = nullptr );

	void CreateRenderTargetTextureB( UINT slices, UINT width, UINT height, DXGI_FORMAT format,	ID3D11Texture2D **texture, ID3D11RenderTargetView **rtv, ID3D11ShaderResourceView **srv );
	void CreateDepthStencilTextureB( UINT slices, UINT width, UINT height,						ID3D11Texture2D **texture, ID3D11DepthStencilView **dsv, ID3D11ShaderResourceView **srv );

	// SAMPLERS
	
	ID3D11SamplerState *CreateLinearSampler	( ID3D11SamplerState **sampler = nullptr );
	ID3D11SamplerState *CreatePointSampler	( ID3D11SamplerState **sampler = nullptr );

	// BLEND STATES
	
	ID3D11BlendState *CreateAdditiveBlendState		( ID3D11BlendState **state = nullptr );
	ID3D11BlendState *CreateSpecialisedBlendStateA	( ID3D11BlendState **state = nullptr );

	// DEPTH STENCIL STATES
	
	ID3D11DepthStencilState *CreateDisabledDepthStencilState( ID3D11DepthStencilState **state = nullptr );
	ID3D11DepthStencilState *CreateEnabledDepthStencilState	( ID3D11DepthStencilState **state = nullptr );

	// RASTERIZER

	ID3D11RasterizerState* CreateNoCullRasterizerState( ID3D11RasterizerState** state = nullptr );
}

#endif