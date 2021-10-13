#include "Direct3D.h"

#include <sstream>

#include "Common.h"
#include "DebugConsole.h"

using std::stringstream;

using console::Print;

ID3D11Device			*gDevice;
ID3D11DeviceContext		*gImmediateContext;
IDXGISwapChain			*gSwapChain;
ID3D11RenderTargetView	*gBackBufferRTV;
ID3D11DepthStencilView	*gBackBufferDSV;
ID3D11Texture2D			*gDepthStencilBuffer;
D3D11_VIEWPORT			gViewport;

void d3d::SetDevice(ID3D11Device *device)
{
	static bool first = true;

	if (first)
	{
		gDevice = device;
		gDevice->AddRef();
		first = false;
	}
	else
	{
		Print("Attempted to reset ID3D11Device", console::RED);
	}
}

void d3d::SetImmediateContext(ID3D11DeviceContext *context)
{
	static bool first = true;

	if (first)
	{
		gImmediateContext = context;
		gImmediateContext->AddRef();
		first = false;
	}
	else
	{
		Print("Attempted to reset ID3D11DeviceContext", console::RED);
	}
}

void d3d::SetSwapChain(IDXGISwapChain *swapChain)
{
	static bool first = true;

	if (first)
	{
		gSwapChain = swapChain;
		gSwapChain->AddRef();
		first = false;
	}
	else
	{
		Print("Attempted to reset IDXGISwapChain", console::RED);
	}
}

void d3d::SetBackBufferRTV(ID3D11RenderTargetView *RTV, bool onResize)
{
	static bool first = true;

	if (first || onResize)
	{
		gBackBufferRTV = RTV;
		gBackBufferRTV->AddRef();
		first = false;
	}
	else
	{
		Print("Attempted to reset ID3D11RenderTargetView", console::RED);
	}
}

void d3d::SetBackBufferDSV(ID3D11DepthStencilView *DSV, bool onResize)
{
	static bool first = true;

	if (first || onResize)
	{
		gBackBufferDSV = DSV;
		gBackBufferDSV->AddRef();
		first = false;
	}
	else
	{
		Print("Attempted to reset ID3D11DepthStencilView", console::RED);
	}
}

void d3d::SetDepthStencilBuffer(ID3D11Texture2D *DSB, bool onResize)
{
	static bool first = true;

	if (first || onResize)
	{
		gDepthStencilBuffer = DSB;
		gDepthStencilBuffer->AddRef();
		first = false;
	}
	else
	{
		Print("Attempted to reset Back Depth Stencil Buffer", console::RED);
	}
}

void d3d::SetViewport(D3D11_VIEWPORT viewport, bool onResize)
{
	static bool first = true;

	if (first || onResize)
	{
		gViewport = viewport;
		first = false;
	}
	else
	{
		Print("Attempted to reset D3D11_VIEWPORT", console::RED);
	}
}

ID3D11Device * const d3d::GetDevice(ID3D11Device **device)
{
	gDevice->AddRef();

	if (device)
		*device = gDevice;

	return gDevice;
}

ID3D11DeviceContext * const d3d::GetImmediateContext(ID3D11DeviceContext **context)
{
	gImmediateContext->AddRef();

	if (context)
		*context = gImmediateContext;

	return gImmediateContext;
}

IDXGISwapChain * const d3d::GetSwapChain(IDXGISwapChain **swapChain)
{
	gSwapChain->AddRef();

	if (swapChain)
		*swapChain = gSwapChain;

	return gSwapChain;
}

ID3D11RenderTargetView * const d3d::GetBackBufferRTV(ID3D11RenderTargetView **RTV)
{
	gBackBufferRTV->AddRef();

	if (RTV)
		*RTV = gBackBufferRTV;

	return gBackBufferRTV;
}

ID3D11DepthStencilView * const d3d::GetBackBufferDSV(ID3D11DepthStencilView **DSV)
{
	gBackBufferDSV->AddRef();

	if (DSV)
		*DSV = gBackBufferDSV;

	return gBackBufferDSV;
}

ID3D11Texture2D * const d3d::GetDepthStencilBuffer(ID3D11Texture2D **DSB)
{
	gDepthStencilBuffer->AddRef();

	if (DSB)
		*DSB = gDepthStencilBuffer;

	return gDepthStencilBuffer;
}

D3D11_VIEWPORT &d3d::GetViewport()
{
	return gViewport;
}

void d3d::Init(HWND hWnd, UINT width, UINT height)
{
	// DEVICE AND CONTEXT CREATION 

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device *device;
	ID3D11DeviceContext *context;

	HRESULT hr = D3D11CreateDevice(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		createDeviceFlags,
		0,
		0,
		D3D11_SDK_VERSION,
		&device,
		&featureLevel,
		&context
		);

	Print(hr, "D3D11CreateDevice");
	Print(featureLevel == D3D_FEATURE_LEVEL_11_0, "Direct3D Feature Level 11");

	d3d::SetDevice(device);
	d3d::SetImmediateContext(context);

	// MSAA CHECK
	UINT msaaQuality;
	hr = device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &msaaQuality);

	stringstream ss;
	ss << "MSAA Quality Level " << msaaQuality;
	Print(hr, ss.str());

	// SWAP CHAIN CREATION

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = 0;	// Going to be reset in Resize() anyway.
	sd.BufferDesc.Height = 0;	// Going to be reset in Resize() anyway.
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (gEnableMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = msaaQuality - 1;
	}
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	// WTF?

	IDXGIDevice* dxgiDevice = 0;
	hr = device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

	IDXGIAdapter* dxgiAdapter = 0;
	hr |= dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

	IDXGIFactory* dxgiFactory = 0;
	hr |= dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	IDXGISwapChain *swapChain;
	hr |= dxgiFactory->CreateSwapChain(device, &sd, &swapChain);
	Print(hr, "CreateSwapChain");

	d3d::SetSwapChain(swapChain);

	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);

	// VIEWPORT

	Resize(width, height);
}

void d3d::Resize(UINT width, UINT height)
{
	ID3D11Device * const device = d3d::GetDevice();
	ID3D11DeviceContext * const context = d3d::GetImmediateContext();

	d3d::ReleaseBackBufferRTV();
	d3d::ReleaseBackBufferDSV();
	d3d::ReleaseBackBufferDSB();

	// RE_CREATE RENDER TARGET

	IDXGISwapChain *swapChain = d3d::GetSwapChain();
	HRESULT hr = swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	ID3D11Texture2D *renderTargetBuffer;
	hr |= swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&renderTargetBuffer));
	ReleaseCOM(swapChain);

	ID3D11RenderTargetView *renderTargetView;
	hr |= device->CreateRenderTargetView(renderTargetBuffer, 0, &renderTargetView);
	ReleaseCOM(renderTargetBuffer);
	Print(hr, "CreateRenderTargetView");

	d3d::SetBackBufferRTV(renderTargetView, true);

	// RE_CREATE DEPTH STENCIL 

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	UINT msaaQuality;
	hr = device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &msaaQuality);

	if (gEnableMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = msaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	ID3D11Texture2D *depthStencilBuffer;
	hr = device->CreateTexture2D(&depthStencilDesc, 0, &depthStencilBuffer);
	Print(hr, "CreateTexture2D: Stencil");

	d3d::SetDepthStencilBuffer(depthStencilBuffer, true);

	ID3D11DepthStencilView *depthStencilView;
	hr = device->CreateDepthStencilView(depthStencilBuffer, 0, &depthStencilView);
	Print(hr, "CreateDepthStencilView");

	d3d::SetBackBufferDSV(depthStencilView, true);

	// done
	context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
	ReleaseCOM(depthStencilBuffer);
	ReleaseCOM(renderTargetView);
	ReleaseCOM(depthStencilView);

	// VIEWPORT

	D3D11_VIEWPORT &viewport = d3d::GetViewport();
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewport);
}

void d3d::Unin()
{
	ReleaseAll();
}

void d3d::ReleaseBackBufferRTV()
{ 
	ReleaseCOM(gBackBufferRTV);
}

void d3d::ReleaseBackBufferDSV()
{
	ReleaseCOM(gBackBufferDSV);
}

void d3d::ReleaseBackBufferDSB()
{
	ReleaseCOM(gDepthStencilBuffer);
}

void d3d::ReleaseAll()
{
	ReleaseCOM(gDevice);
	ReleaseCOM(gImmediateContext);
	ReleaseCOM(gSwapChain);
	ReleaseCOM(gBackBufferRTV);
	ReleaseCOM(gBackBufferDSV);
	ReleaseCOM(gDepthStencilBuffer);
}