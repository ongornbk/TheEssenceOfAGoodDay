#pragma once
#include "corestd.h"
#include "String.h"

class Window
{
public:
	virtual int32 Initialize(int32 width, int32 height,String title,bool fullscreen = false) = 0;
	virtual int32 Update() = 0;

protected:

	HINSTANCE m_hInstance{};
	HWND      m_hwnd{};
	HDC       m_hdc{};
	String    applicationName;
	String    windowName;

	bool      fullscreen;
};