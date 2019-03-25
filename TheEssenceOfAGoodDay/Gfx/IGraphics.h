#pragma once
#include "..\Core\Src\String.h"

#define GRAPHICS_FLAG_FULLSCREEN (1 << 0)
#define GRAPHICS_FLAG_VSYNC      (1 << 1)

class IGraphics
{
public:
	virtual int32 Initialize(const int32 screenWidth, const int32 screenHeight, const HWND hwnd, const uint8 flags) = 0;

protected:

	uint8 m_flags;
};