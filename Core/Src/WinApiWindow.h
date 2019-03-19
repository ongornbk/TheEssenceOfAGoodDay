#pragma once
#include "Window.h"

class WinApiWindow : public Window
{

public:
	int32 Initialize(int32 width, int32 height,String title,bool fullscreen = false) override;
	int32 Update() override;

};