#include "Factory.h"

#include <D3Dcompiler.h>

#include "Common.h"
#include "DebugConsole.h"
#include "Direct3D.h"

#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "DXGUID.lib")

using console::Print;

// VERTEX SHADER

ID3D11VertexShader *factory::CreateVertexShaderFromFile( LPCWSTR file, LPCSTR funcName, ID3D11ShaderReflection **reflection )
{
	ID3D11Device *aDevice = d3d::GetDevice();

	ID3D10Blob *compiledShader;
	ID3D10Blob *errorMessages;
	HRESULT hr = D3DX11CompileFromFile(
		file,
		NULL,
		NULL,
		funcName,
		"vs_5_0",
		0,
		0,
		NULL,
		&compiledShader,
		&errorMessages,
		NULL
	);

	Print(hr, "D3DX11CompileFromFile: Vertex");

	if (errorMessages)
		Print(static_cast<char *>(errorMessages->GetBufferPointer()), console::RED);

	ReleaseCOM(errorMessages);

	ID3D11VertexShader *vertexShader;
	hr = aDevice->CreateVertexShader(
		compiledShader->GetBufferPointer(),
		compiledShader->GetBufferSize(),
		NULL,
		&vertexShader
	);
	Print(hr, "CreateVertexShader");

	if (reflection != nullptr)
	{
		// get shader reflection
		hr = D3DReflect(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)reflection);
		Print(hr, "Reflect");
	}

	ReleaseCOM(compiledShader);
	ReleaseCOM( aDevice );

	return vertexShader;
}

void factory::CreateVertexShaderAndInputLayoutFromFile(LPCWSTR file, LPCSTR funcName, D3D11_INPUT_ELEMENT_DESC *inputElementDescs, UINT numElements, ID3D11VertexShader **vertexShader, ID3D11InputLayout **inputLayout, ID3D11ShaderReflection **reflection)
{
	// CREATE VERTEX SHADER

	ID3D11Device *aDevice = d3d::GetDevice();

	ID3D10Blob *compiledShader;
	ID3D10Blob *errorMessages;
	HRESULT hr = D3DX11CompileFromFile(
		file,
		NULL,
		NULL,
		funcName,
		"vs_5_0",
		0,
		0,
		NULL,
		&compiledShader,
		&errorMessages,
		NULL
	);

	Print(hr, "D3DX11CompileFromFile: Vertex");

	if (errorMessages)
		Print(static_cast<char *>(errorMessages->GetBufferPointer()), console::RED);

	ReleaseCOM(errorMessages);

	hr = aDevice->CreateVertexShader(
		compiledShader->GetBufferPointer(),
		compiledShader->GetBufferSize(),
		NULL,
		vertexShader
	);

	Print(hr, "CreateVertexShader");

	// CREATE INPUT LAYOUT

	hr = aDevice->CreateInputLayout(
		inputElementDescs, 
		numElements, 
		compiledShader->GetBufferPointer(), 
		compiledShader->GetBufferSize(), 
		inputLayout
	);
	Print(hr, "CreateInputLayout");

	if (reflection != nullptr)
	{
		// get shader reflection
		hr = D3DReflect(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)reflection);
		Print(hr, "Reflect");
	}

	ReleaseCOM(compiledShader);
	ReleaseCOM( aDevice );
}

// HULL SHADER

ID3D11HullShader *factory::CreateHullShaderFromFile( LPCWSTR file, LPCSTR funcName, ID3D11ShaderReflection **reflection )
{
	ID3D11Device *aDevice = d3d::GetDevice();

	ID3D10Blob *compiledShader;
	ID3D10Blob *errorMessages;
	HRESULT hr = D3DX11CompileFromFile(
		file,
		NULL,
		NULL,
		funcName,
		"hs_5_0",
		0,
		0,
		NULL,
		&compiledShader,
		&errorMessages,
		NULL
	);

	Print(hr, "D3DX11CompileFromFile: Hull");

	if (errorMessages)
		Print(static_cast<char *>(errorMessages->GetBufferPointer()), console::RED);

	ReleaseCOM(errorMessages);

	ID3D11HullShader *hullShader;
	hr = aDevice->CreateHullShader(
		compiledShader->GetBufferPointer(),
		compiledShader->GetBufferSize(),
		NULL,
		&hullShader
	);
	Print(hr, "CreateHullShader");


	if (reflection != nullptr)
	{
		// get shader reflection
		hr = D3DReflect(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)reflection);
		Print(hr, "Reflect");
	}

	ReleaseCOM( compiledShader );
	ReleaseCOM( aDevice );

	return hullShader;
}

// DOMAIN SHADER

ID3D11DomainShader *factory::CreateDomainShaderFromFile( LPCWSTR file, LPCSTR funcName, ID3D11ShaderReflection **reflection )
{
	ID3D11Device *aDevice = d3d::GetDevice();

	ID3D10Blob *compiledShader;
	ID3D10Blob *errorMessages;
	HRESULT hr = D3DX11CompileFromFile(
		file,
		NULL,
		NULL,
		funcName,
		"ds_5_0",
		0,
		0,
		NULL,
		&compiledShader,
		&errorMessages,
		NULL
	);

	Print(hr, "D3DX11CompileFromFile: Domain");

	if (errorMessages)
		Print(static_cast<char *>(errorMessages->GetBufferPointer()), console::RED);

	ReleaseCOM(errorMessages);

	ID3D11DomainShader *domainShader;
	hr = aDevice->CreateDomainShader(
		compiledShader->GetBufferPointer(),
		compiledShader->GetBufferSize(),
		NULL,
		&domainShader
	);
	Print(hr, "CreateDomainShader");


	if (reflection != nullptr)
	{
		// get shader reflection
		hr = D3DReflect(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)reflection);
		Print(hr, "Reflect");
	}

	ReleaseCOM( compiledShader );
	ReleaseCOM( aDevice );

	return domainShader;
}

// GEOMETRY SHADER

ID3D11GeometryShader *factory::CreateGeometryShaderFromFile( LPCWSTR file, LPCSTR funcName, ID3D11ShaderReflection **reflection )
{
	ID3D11Device *aDevice = d3d::GetDevice();

	ID3D10Blob *compiledShader;
	ID3D10Blob *errorMessages;
	HRESULT hr = D3DX11CompileFromFile(
		file,
		NULL,
		NULL,
		funcName,
		"gs_5_0",
		0,
		0,
		NULL,
		&compiledShader,
		&errorMessages,
		NULL
	);

	Print(hr, "D3DX11CompileFromFile: Geometry");

	if (errorMessages)
		Print(static_cast<char *>(errorMessages->GetBufferPointer()), console::RED);

	ReleaseCOM(errorMessages);

	ID3D11GeometryShader *geometryShader;
	hr = aDevice->CreateGeometryShader(
		compiledShader->GetBufferPointer(),
		compiledShader->GetBufferSize(),
		NULL,
		&geometryShader
	);
	Print(hr, "CreateGeometryShader");


	if (reflection != nullptr)
	{
		// get shader reflection
		hr = D3DReflect(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)reflection);
		Print(hr, "Reflect");
	}

	ReleaseCOM( compiledShader );
	ReleaseCOM( aDevice );

	return geometryShader;
}

// PIXEL SHADER

ID3D11PixelShader *factory::CreatePixelShaderFromFile(LPCWSTR file, LPCSTR funcName, ID3D11ShaderReflection **reflection)
{
	ID3D11Device *aDevice = d3d::GetDevice();

	ID3D10Blob *compiledShader;
	ID3D10Blob *errorMessages;
	HRESULT hr = D3DX11CompileFromFile(
		file,
		NULL,
		NULL,
		funcName,
		"ps_5_0",
		0,
		0,
		NULL,
		&compiledShader,
		&errorMessages,
		NULL
	);

	Print(hr, "D3DX11CompileFromFile: Pixel");

	if (errorMessages)
		Print(static_cast<char *>(errorMessages->GetBufferPointer()), console::RED);

	ReleaseCOM(errorMessages);

	ID3D11PixelShader *pixelShader;
	hr = aDevice->CreatePixelShader(
		compiledShader->GetBufferPointer(),
		compiledShader->GetBufferSize(),
		NULL,
		&pixelShader
	);
	Print(hr, "CreatePixelShader");


	if (reflection != nullptr)
	{
		// get shader reflection
		hr = D3DReflect(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)reflection);
		Print(hr, "Reflect");
	}

	ReleaseCOM(compiledShader);
	ReleaseCOM( aDevice );

	return pixelShader;
}

// VERTEX BUFFER

ID3D11Buffer *factory::CreateVertexBuffer(bool streamOut, bool cpuAccess, const float * const data, UINT byteWidth)
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_BUFFER_DESC vbd;

	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	if (streamOut)
		vbd.BindFlags |= D3D10_BIND_STREAM_OUTPUT;

	vbd.ByteWidth = byteWidth;

	if (cpuAccess)
	{
		vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vbd.Usage = D3D11_USAGE_DYNAMIC;
	}
	else
	{
		vbd.CPUAccessFlags = 0;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
	}

	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	HRESULT hr;
	ID3D11Buffer *vertexBuffer;
	if (data)
	{
		D3D11_SUBRESOURCE_DATA vertexInitData;
		vertexInitData.pSysMem = &data[0];
		hr = aDevice->CreateBuffer(&vbd, &vertexInitData, &vertexBuffer);
	}
	else
	{
		hr = aDevice->CreateBuffer(&vbd, NULL, &vertexBuffer);
	}
	
	ReleaseCOM( aDevice );

	Print(hr, "CreateBuffer: Vertex");

	return vertexBuffer;
}

ID3D11Buffer *factory::CreateIndexBuffer(bool cpuAccess, const UINT * const data, UINT byteWidth)
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_BUFFER_DESC ibd;

	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	ibd.ByteWidth = byteWidth;

	if (cpuAccess)
	{
		ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ibd.Usage = D3D11_USAGE_DYNAMIC;
	}
	else
	{
		ibd.CPUAccessFlags = 0;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
	}

	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexInitData;
	indexInitData.pSysMem = &data[0];

	ID3D11Buffer *indexBuffer;
	HRESULT hr = aDevice->CreateBuffer(&ibd, &indexInitData, &indexBuffer);
	
	ReleaseCOM( aDevice );

	Print(hr, "CreateBuffer: Index");

	return indexBuffer;
}

ID3D11Buffer *factory::CreateStagingBuffer(UINT byteWidth, ID3D11Buffer **buffer)
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_BUFFER_DESC vbd;

	vbd.BindFlags = 0;
	vbd.ByteWidth = byteWidth;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	vbd.Usage = D3D11_USAGE_STAGING;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	ID3D11Buffer *tmpBuffer;
	HRESULT hr = aDevice->CreateBuffer(&vbd, NULL, &tmpBuffer);
	
	ReleaseCOM( aDevice );

	Print(hr, "CreateBuffer: Staging");

	if (buffer) 
		*buffer = tmpBuffer;

	return tmpBuffer;
}

ID3D11Buffer *factory::CreateConstantBuffer(bool updatable, const float * const data, UINT byteWidth, ID3D11Buffer **buffer)
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_BUFFER_DESC vbd;

	vbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vbd.ByteWidth = byteWidth;
	vbd.CPUAccessFlags = 0;

	if (updatable)
	{
		vbd.Usage = D3D11_USAGE_DEFAULT;
	}
	else
	{
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
	}

	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	HRESULT hr;
	ID3D11Buffer *tmpBuffer;
	if (data)
	{
		D3D11_SUBRESOURCE_DATA constantInitData;
		constantInitData.pSysMem = &data[0];
		hr = aDevice->CreateBuffer(&vbd, &constantInitData, &tmpBuffer);
	}
	else
	{
		hr = aDevice->CreateBuffer(&vbd, NULL, &tmpBuffer);
	}
	
	ReleaseCOM( aDevice );

	Print(hr, "CreateBuffer: Constant");

	if (buffer)
		*buffer = tmpBuffer;

	return tmpBuffer;
}

ID3D11Texture2D *factory::CreateRenderTargetTexture2D(UINT width, UINT height, DXGI_FORMAT format, bool cpuAccess, ID3D11Texture2D **texture)
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_TEXTURE2D_DESC td;
	td.ArraySize = 1;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

	if (cpuAccess)
	{
		td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		td.Usage = D3D11_USAGE_DEFAULT;
	}
	else
	{
		td.CPUAccessFlags = 0;
		td.Usage = D3D11_USAGE_IMMUTABLE;
	}

	td.Format = format;
	td.Height = height;
	td.MipLevels = 1;
	td.MiscFlags = 0;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Width = width;

	ID3D11Texture2D *tmpTexture;
	HRESULT hr = aDevice->CreateTexture2D(&td, NULL, &tmpTexture);
	Print(hr, "CreateTexture2D");
	
	ReleaseCOM( aDevice );

	if (texture)
		*texture = tmpTexture;

	return tmpTexture;
}

void factory::CreateRenderTargetTextureB( UINT slices, UINT width, UINT height, DXGI_FORMAT format, ID3D11Texture2D **texture, ID3D11RenderTargetView **rtv, ID3D11ShaderResourceView **srv )
{
	ID3D11Device *aDevice = d3d::GetDevice();

	/*
		Create Texture 2D
	*/
	
	D3D11_TEXTURE2D_DESC td;
	td.ArraySize = slices;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	td.CPUAccessFlags = 0;
	td.Format = format;
	td.Height = height;
	td.MipLevels = 1;
	td.MiscFlags = 0;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.Width = width;

	HRESULT hr = aDevice->CreateTexture2D(&td, NULL, texture);
	Print(hr, "CreateTexture2D");
	
	/*
		Create Render Target View
	*/

	D3D11_RENDER_TARGET_VIEW_DESC rtvd;
	rtvd.Format = format;

	switch ( slices )
	{
	case 1:
		rtvd.ViewDimension		= D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvd.Texture2D.MipSlice = 0;
		break;
	default:
		rtvd.ViewDimension					= D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		rtvd.Texture2DArray.ArraySize		= slices;
		rtvd.Texture2DArray.FirstArraySlice = 0;
		rtvd.Texture2D.MipSlice				= 0;
		break;
	}

	hr = aDevice->CreateRenderTargetView(*texture, &rtvd, rtv);
	Print(hr, "CreateRenderTargetView");

	/*
		Create Resource Shader View
	*/
	
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	srvd.Format = format;

	switch ( slices )
	{
	case 1:
		srvd.ViewDimension				= D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MipLevels		= 1;
		srvd.Texture2D.MostDetailedMip	= 0;
		break;
	default:
		srvd.ViewDimension					= D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		srvd.Texture2DArray.ArraySize		= slices;
		srvd.Texture2DArray.FirstArraySlice = 0;
		srvd.Texture2D.MipLevels			= 1;
		srvd.Texture2D.MostDetailedMip		= 0;
		break;
	}

	hr = aDevice->CreateShaderResourceView(*texture, &srvd, srv);
	Print(hr, "CreateShaderResourceView");

	// Release device
	ReleaseCOM( aDevice );
}

void factory::CreateDepthStencilTextureB( UINT slices, UINT width, UINT height, ID3D11Texture2D **texture, ID3D11DepthStencilView **dsv, ID3D11ShaderResourceView **srv )
{	
	ID3D11Device *aDevice = d3d::GetDevice();

	/*
		Create Depth Stencil Texture
	*/

	D3D11_TEXTURE2D_DESC td;
	td.ArraySize			= slices;
	td.BindFlags			= D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags		= 0;
	td.Format				= DXGI_FORMAT_R24G8_TYPELESS;
	td.Height				= height;
	td.MipLevels			= 1;
	td.MiscFlags			= 0;
	td.SampleDesc.Count		= 1;
	td.SampleDesc.Quality	= 0;
	td.Usage				= D3D11_USAGE_DEFAULT;
	td.Width				= width;

	HRESULT hr = aDevice->CreateTexture2D(&td, NULL, texture);
	Print(hr, "CreateTexture2D: Stencil");
	
	/*
		Create Depth Stencil View
	*/

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;					
	dsvd.Flags = 0;										
    dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;			

	switch ( slices )
	{
	case 1:
		dsvd.ViewDimension		= D3D11_DSV_DIMENSION_TEXTURE2D;	
		dsvd.Texture2D.MipSlice = 0;	
		break;
	default:
		dsvd.ViewDimension					= D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
		dsvd.Texture2DArray.ArraySize		= slices;
		dsvd.Texture2DArray.FirstArraySlice = 0;
		dsvd.Texture2D.MipSlice				= 0;	
		break;
	}
						
	hr = aDevice->CreateDepthStencilView( *texture, &dsvd, dsv );
	Print( hr, "CreateDepthStencilView" );

	/*
		Create Depth Stencil Resource View
	*/
	
    D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
    srvd.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	
	switch ( slices )
	{
	case 1:
		srvd.ViewDimension				= D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MipLevels		= 1;
		srvd.Texture2D.MostDetailedMip	= 0;
		break;
	default:
		srvd.ViewDimension					= D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		srvd.Texture2DArray.ArraySize		= slices;
		srvd.Texture2DArray.FirstArraySlice = 0;
		srvd.Texture2D.MipLevels			= 1;
		srvd.Texture2D.MostDetailedMip		= 0;
		break;
	}

	hr = aDevice->CreateShaderResourceView( *texture, &srvd, srv );
	Print( hr, "CreateShaderResourceView: Depth" );

	// Release device
	ReleaseCOM( aDevice );
}

ID3D11SamplerState *factory::CreateLinearSampler(ID3D11SamplerState **sampler)
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState *tmpSampler;
	HRESULT hr = aDevice->CreateSamplerState(&sd, &tmpSampler);
	Print(hr, "CreateSamplerState : Linear");
	
	ReleaseCOM( aDevice );

	if (sampler)
		*sampler = tmpSampler;

	return tmpSampler;
}

ID3D11SamplerState *factory::CreatePointSampler( ID3D11SamplerState **sampler )
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState *tmpSampler;
	HRESULT hr = aDevice->CreateSamplerState(&sd, &tmpSampler);
	Print(hr, "CreateSamplerState : Point");
	
	ReleaseCOM( aDevice );

	if (sampler)
		*sampler = tmpSampler;

	return tmpSampler;
}

ID3D11BlendState *factory::CreateAdditiveBlendState(ID3D11BlendState **state)
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_BLEND_DESC bd;
	bd.AlphaToCoverageEnable = false;
	bd.IndependentBlendEnable = false;

	bd.RenderTarget[0].BlendEnable				= true;
	bd.RenderTarget[0].SrcBlend					= D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend				= D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp					= D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha			= D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha				= D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;

	ID3D11BlendState *tmpState;
	HRESULT hr = aDevice->CreateBlendState(&bd, &tmpState);
	Print(hr, "CreateBlendState");
	
	ReleaseCOM( aDevice );

	if (state)
		*state = tmpState;

	return tmpState;
}

ID3D11BlendState* factory::CreateSpecialisedBlendStateA( ID3D11BlendState **state )
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_BLEND_DESC bd;
	bd.AlphaToCoverageEnable = false;
	bd.IndependentBlendEnable = false;

	bd.RenderTarget[0].BlendEnable				= true;
	bd.RenderTarget[0].SrcBlend					= D3D11_BLEND_INV_DEST_ALPHA;
	bd.RenderTarget[0].DestBlend				= D3D11_BLEND_DEST_ALPHA;
	bd.RenderTarget[0].BlendOp					= D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha			= D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha				= D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;

	ID3D11BlendState *tmpState;
	HRESULT hr = aDevice->CreateBlendState(&bd, &tmpState);
	Print(hr, "CreateBlendState");
	
	ReleaseCOM( aDevice );

	if ( state )
		*state = tmpState;

	return tmpState;
}

ID3D11DepthStencilState *factory::CreateDisabledDepthStencilState(ID3D11DepthStencilState **state)
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_DEPTH_STENCIL_DESC dsd;
	dsd.DepthEnable = false;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsd.DepthFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil test parameters
	dsd.StencilEnable = false;
	dsd.StencilReadMask = 0xFF;
	dsd.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	ID3D11DepthStencilState *tmpState;
	HRESULT hr = aDevice->CreateDepthStencilState(&dsd, &tmpState);
	Print(hr, "CreateDepthStencilState");
	
	ReleaseCOM( aDevice );

	if (state)
		*state = tmpState;

	return tmpState;
}

ID3D11DepthStencilState *factory::CreateEnabledDepthStencilState(ID3D11DepthStencilState **state)
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_DEPTH_STENCIL_DESC dsd;
	dsd.DepthEnable = true;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;

	// Stencil test parameters
	dsd.StencilEnable = false;
	dsd.StencilReadMask = 0xFF;
	dsd.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	ID3D11DepthStencilState *tmpState;
	HRESULT hr = aDevice->CreateDepthStencilState(&dsd, &tmpState);
	Print(hr, "CreateDepthStencilState");
	
	ReleaseCOM( aDevice );

	if (state)
		*state = tmpState;

	return tmpState;
}

ID3D11RasterizerState* factory::CreateNoCullRasterizerState( ID3D11RasterizerState** state )
{
	ID3D11Device *aDevice = d3d::GetDevice();

	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_FRONT;
	rd.FrontCounterClockwise = false;
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = false;
	rd.AntialiasedLineEnable = false;

	ID3D11RasterizerState* tmpState;
	HRESULT hr = aDevice->CreateRasterizerState( &rd, &tmpState );
	Print( hr, "CreateRasterizerState" );
	
	ReleaseCOM( aDevice );

	if ( state )
		*state = tmpState;

	return tmpState;
}