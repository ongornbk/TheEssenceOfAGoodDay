#include "DirectX11.h"

DirectX11::DirectX11(void)
{
	m_swapChain = nullptr;
	m_device = nullptr;
	m_deviceContext = nullptr;
	m_renderTargetView = nullptr;
	m_depthStencilBuffer = nullptr;
	m_depthStencilState[0] = nullptr;
	m_depthStencilState[1] = nullptr;
	m_depthStencilView = nullptr;
	m_rasterState = nullptr;
	m_alphaBlendingState[0] = nullptr;
	m_alphaBlendingState[1] = nullptr;

}

DirectX11::~DirectX11(void)
{
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, nullptr);
	}


	safe_release(m_alphaBlendingState[0]);
	safe_release(m_alphaBlendingState[1]);
	safe_release(m_device);
	safe_release(m_deviceContext);
	safe_release(m_renderTargetView);
	safe_release(m_depthStencilBuffer);
	safe_release(m_depthStencilState[0]);
	safe_release(m_depthStencilState[1]);
	safe_release(m_depthStencilView);
	safe_release(m_rasterState);
}

int32 DirectX11::Initialize(const int32 screenWidth, const int32 screenHeight, const HWND hwnd, const uint8 flags)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	UINT numModes = 0u, numerator = 0u, denominator = 0u;
	size_t stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int32 error;
	ID3D11Texture2D* backBufferPtr;

	m_flags = flags;

	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
	{
		return 1;
	}

	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
	{
		return 2;
	}
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
	{
		return 3;
	}

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))
	{
		return 4;
	}
	displayModeList = new DXGI_MODE_DESC[numModes];

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
	{
		return 5;
	}

	for (auto i = 0u; i < numModes; ++i)
	{
		if (displayModeList[i].Width == (uint32)screenWidth)
		{
			if (displayModeList[i].Height == (uint32)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	if (numerator == 0u && denominator == 0u)
	{
		return 6;
	}

	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return 7;
	}

	m_videoCardMemory = (int32)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
	error = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);

	if (error != 0)
	{
		return 8;
	}

	if (displayModeList)
	{
		delete[] displayModeList;
		displayModeList = NULL;
	}

	safe_release(adapterOutput);
	safe_release(adapter);
	safe_release(factory);

	if (InitializeSwapChain(hwnd, flags & GRAPHICS_FLAG_FULLSCREEN, screenWidth, screenHeight, numerator, denominator))
	{
		return 9;
	}

	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	if (FAILED(result))
	{
		return 10;
	}

	result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
	if (FAILED(result))
	{
		return 11;
	}

	safe_release(backBufferPtr);


	if (InitializeDepthBuffer(screenWidth, screenHeight))
	{
		return 12;
	}

	if (InitializeDepthStencilBuffer())
	{
		return 13;
	}

	if (InitializeStencilView())
	{
		return 14;
	}

	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	if (InitializeRasterizerState())
	{
		return 15;
	}

	if (InitializeViewport(screenWidth, screenHeight))
	{
		return 16;
	}
	if (InitializeAlphaBlending())
	{
		return 17;
	}

	if (InitializeZBuffer())
	{
		return 18;
	}

	return 0;

}

void DirectX11::Begin(const float r,const  float g,const float b,const float a) const
{
	float color[4];
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;

	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.f, 0);
}

void DirectX11::End() const
{
	m_swapChain->Present(m_flags & GRAPHICS_FLAG_VSYNC, 0);
}

void DirectX11::EnableAlphaBlending(bool enable)
{
	const float blendFactor[4]{};
	m_deviceContext->OMSetBlendState(m_alphaBlendingState[enable], blendFactor, 0xffffffff);
}

void DirectX11::EnableZBuffer(bool enable)
{
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState[enable], 1);
}

void DirectX11::Release()
{
	delete(this);
}

ID3D11Device * DirectX11::GetDevice()
{
	return m_device;
}

ID3D11DeviceContext * DirectX11::GetDeviceContext()
{
	return m_deviceContext;
}

int32 DirectX11::InitializeSwapChain(HWND hwnd,const bool fullscreen,const int32 screenWidth,const int32 screenHeight,const uint32 numerator,const uint32 denominator)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT result;

	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;

	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	if (m_flags & GRAPHICS_FLAG_VSYNC)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	swapChainDesc.OutputWindow = hwnd;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !fullscreen;

	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	swapChainDesc.Flags = 0;

	featureLevel = D3D_FEATURE_LEVEL_11_0;

	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);
	if (FAILED(result))
	{
		return 1;
	}



	return 0;
}

int32 DirectX11::InitializeDepthBuffer(const int32 screenWidth,const int32 screenHeight)
{
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	HRESULT result;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
	if (FAILED(result))
	{
		return 1;
	}

	return 0;
}

int32 DirectX11::InitializeStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	HRESULT result;

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if (FAILED(result))
	{
		return 1;
	}


	return 0;
}

int32 DirectX11::InitializeDepthStencilBuffer()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	HRESULT result;

	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState[1]);
	if (FAILED(result))
	{
		return 1;
	}

	m_deviceContext->OMSetDepthStencilState(m_depthStencilState[0], 1);

	return 0;
}

int32 DirectX11::InitializeRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterDesc;
	HRESULT result;

	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = false;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(result))
	{
		return 1;
	}

	m_deviceContext->RSSetState(m_rasterState);

	return 0;
}

int32 DirectX11::InitializeViewport(const int32 screenWidth,const int32 screenHeight)
{
	D3D11_VIEWPORT viewport;

	viewport.Width = (float)(screenWidth);
	viewport.Height = (float)(screenHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	m_deviceContext->RSSetViewports(1, &viewport);

	return 0;
}

int32 DirectX11::InitializeAlphaBlending()
{
	D3D11_BLEND_DESC blendStateDesc;

	HRESULT result;
	ZeroMemory(&blendStateDesc, sizeof(D3D11_BLEND_DESC));
	blendStateDesc.RenderTarget[0].BlendEnable = true;
	blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;


	result = m_device->CreateBlendState(&blendStateDesc, &m_alphaBlendingState[0]);
	if (FAILED(result))
	{
		return 1;
	}

	blendStateDesc.RenderTarget[0].BlendEnable = false;

	result = m_device->CreateBlendState(&blendStateDesc, &m_alphaBlendingState[1]);
	if (FAILED(result))
	{
		return 2;
	}

	return 0;
}

int32 DirectX11::InitializeZBuffer()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	HRESULT result;

	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));


	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState[1]);
	if (FAILED(result))
	{
		return 1;
	}

	return 0;
}