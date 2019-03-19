#pragma once
#include "Window.h"

class WinApiWindow : public Window
{

public:
	virtual int32 Initialize(int32 width, int32 height,String title,bool fullscreen = false) override;
	virtual int32 Update() override;

protected:

	void(__stdcall*      m_callback)(void);
};