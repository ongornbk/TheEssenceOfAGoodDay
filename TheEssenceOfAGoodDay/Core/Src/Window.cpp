#include "Window.h"

HINSTANCE Window::GetHinstance() const noexcept
{
	return m_hInstance;
}

HWND Window::GetHWND() const noexcept
{
	return m_hwnd;
}
HDC Window::GetHDC() const noexcept
{
	return m_hdc;
}