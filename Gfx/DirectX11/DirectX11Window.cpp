#include "DirectX11Window.h"

int32 DirectX11Window::Initialize(int32 width, int32 height, String title, bool fullscreen)
{
	return WinApiWindow::Initialize(width,height,title,fullscreen);
}
int32 DirectX11Window::Update()
{
	return WinApiWindow::Update();
}
