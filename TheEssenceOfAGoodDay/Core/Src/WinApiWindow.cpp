#include "WinApiWindow.h"

LRESULT CALLBACK WndProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(WM_CLOSE);
		break;
	}break;

	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

int32 WinApiWindow::Initialize(int32 width, int32 height, String title,bool fullscreen)
{
	WNDCLASSEX wc;
	applicationName = title;
	windowName = title;
	m_hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = applicationName.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		return 1;
	}

	int32 screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int32 screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (uint32)screenWidth;
		dmScreenSettings.dmPelsHeight = (uint32)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		screenWidth = width;
		screenHeight = height;
	}

	int32 nStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX;

	const int32 xce = (screenWidth - width) / 2;
	const int32 yce = (screenHeight - height) / 2;

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, windowName.c_str(), windowName.c_str(), nStyle, xce, yce, screenWidth, screenHeight, NULL, NULL, m_hInstance, NULL);

	if (m_hwnd == NULL)
	{
		PostQuitMessage(0);
		return 2;
	}

	m_hdc = GetDC(m_hwnd);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	return 0;
}

int32 WinApiWindow::Update()
{

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0u, 0u, PM_REMOVE))
		{
			(void)TranslateMessage(&msg);
			(void)DispatchMessage(&msg);
		}
		else
		{
			//ipp::Timer::Update();
			//Engine::GetEngine()->Run();
		}
	}

	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	return 0;
}