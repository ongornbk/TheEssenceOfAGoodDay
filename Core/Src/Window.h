#pragma once
#include "corestd.h"

class Window
{
public:
	virtual int32 Initialize(int32 width, int32 height, const char* title) = 0;
	virtual int32 Update() = 0;

};