#pragma once
#include "..\..\Core\Src\corestd.h"

#include <d3d11_2.h>
#include <directxmath.h>
#include <directxcolors.h>

class DirectX11
{
public:
	DirectX11(void);
	~DirectX11(void);

private:
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	ID3D11BlendState* m_alphaEnableBlendingState;
	ID3D11BlendState* m_alphaDisableBlendingState;
	ID3D11DepthStencilState* m_depthDisabledStencilState;
};