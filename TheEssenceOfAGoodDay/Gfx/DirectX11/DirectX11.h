#pragma once
#include "..\IGraphics.h"

#include <d3d11_2.h>
#include <directxmath.h>
#include <directxcolors.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

class DirectX11 : public IGraphics
{

public:
	DirectX11(void);
	~DirectX11(void);

	int32 Initialize(const int32 screenWidth,const int32 screenHeight,const HWND hwnd,const uint8 flags) override;

	void Begin(const float r,const float g,const float b,const float a) const;
	void End() const;
	void EnableAlphaBlending(bool enable);
	void EnableZBuffer(bool enable);
	void Release();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

private:

	int32 m_videoCardMemory;
	char m_videoCardDescription[128];

	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;

	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	ID3D11BlendState* m_alphaBlendingState[2];
	//[0] -> enabled;
	//[1] -> disabled;
	ID3D11DepthStencilState* m_depthStencilState[2];
	//[0] -> enabled;
    //[1] -> disabled;

	int32 InitializeSwapChain(HWND hwnd,const bool fullscreen,const int32 screenWidth,const int32 screenHeight,const uint32 numerator,const uint32 denominator);
	int32 InitializeDepthBuffer(const int32 screenWidth,const int32 screenHeight);
	int32 InitializeDepthStencilBuffer();
	int32 InitializeStencilView();
	int32 InitializeRasterizerState();
	int32 InitializeViewport(const int32 screenWidth,const int32 screenHeight);
	int32 InitializeAlphaBlending();
	int32 InitializeZBuffer();
};