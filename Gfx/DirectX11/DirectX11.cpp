#include "DirectX11.h"

DirectX11::DirectX11(void)
{
	m_swapChain = nullptr;
	m_device = nullptr;
	m_deviceContext = nullptr;
	m_renderTargetView = nullptr;
	m_depthStencilBuffer = nullptr;
	m_depthStencilState = nullptr;
	m_depthStencilView = nullptr;
	m_rasterState = nullptr;
	m_alphaDisableBlendingState = nullptr;
	m_alphaEnableBlendingState = nullptr;
	m_depthDisabledStencilState = nullptr;

}

DirectX11::~DirectX11(void)
{
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, nullptr);
	}
	if (m_alphaDisableBlendingState)
	{
		(void)m_alphaDisableBlendingState->Release();
		m_alphaDisableBlendingState = nullptr;
	}
	if (m_device)
	{
		(void)m_device->Release();
		m_device = nullptr;
	}
	if (m_deviceContext)
	{
		(void)m_deviceContext->Release();
		m_deviceContext = nullptr;
	}
	if (m_renderTargetView)
	{
		(void)m_renderTargetView->Release();
		m_renderTargetView = nullptr;
	}
	if (m_depthStencilBuffer)
	{
		(void)m_depthStencilBuffer->Release();
		m_depthStencilBuffer = nullptr;
	}
	if (m_depthStencilState)
	{
		(void)m_depthStencilState->Release();
		m_depthStencilState = nullptr;
	}
	if (m_depthStencilView)
	{
		(void)m_depthStencilView->Release();
		m_depthStencilView = nullptr;
	}
	if (m_rasterState)
	{
		(void)m_rasterState->Release();
		m_rasterState = nullptr;
	}
	if (m_depthDisabledStencilState)
	{
		(void)m_depthDisabledStencilState->Release();
		m_depthDisabledStencilState = nullptr;
	}
	if (m_alphaEnableBlendingState)
	{
		(void)m_alphaEnableBlendingState->Release();
		m_alphaEnableBlendingState = nullptr;
	}



}