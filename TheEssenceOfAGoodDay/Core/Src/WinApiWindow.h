#pragma once
#include "Window.h"

class WinApiWindow : public Window
{

public:
	virtual int32 Initialize(int32 width, int32 height,String title,bool fullscreen = false) override;
	virtual int32 Update() override;

	virtual int32 GetWidth() const noexcept override;
	virtual int32 GetHeight() const noexcept override;

	virtual void SetCallbackFunction(void(__stdcall* callback)(void));

protected:

	void(__stdcall*      m_callback)(void) {};

	int32 m_screenWidth;
	int32 m_screenHeight;
};		  